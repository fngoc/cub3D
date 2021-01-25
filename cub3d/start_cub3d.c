#include "cub3d.h"

/*
** print_map: печать карты.
*/

static  void    print_map(t_cub *cub)
{
    cub->data.img = mlx_new_image(cub->mlx, cub->p.resolution_w, cub->p.resolution_l);
    cub->data.addr = mlx_get_data_addr(cub->data.img, &cub->data.bits_per_pixel, &cub->data.line_length, &cub->data.endian);

    int x = 0;
    while (x++ < cub->p.resolution_w)
    {
        //вычислить положение и направление луча
        double cameraX = 2 * x / (double)cub->p.resolution_w - 1; //x-координата в пространстве камеры
        double rayDirX = cub->plr.dirX + cub->plr.planeX * cameraX;
        double rayDirY = cub->plr.dirY + cub->plr.planeY * cameraX;

        //в каком квадрате карты мы находимся
        int mapX = (int)(cub->plr.y);
        int mapY = (int)(cub->plr.x);

        //длина луча от текущей позиции до следующей стороны x или y
        double sideDistX;
        double sideDistY;

        //длина луча от одной стороны x или y до следующей стороны x или y
        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        //в каком направлении делать шаг в направлении x или y (либо +1, либо -1)
        int stepX;
        int stepY;

        int hit = 0; //был ли удар в стену?
        int side; //была ли поражена стена НС или РЭБ?
        //вычислить шаг и начальную сторону Dist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (cub->plr.y - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - cub->plr.y) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (cub->plr.x - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - cub->plr.x) * deltaDistY;
        }
        //проанализировать ДВР
        while (hit == 0)
        {
            //переход к следующему квадрату карты, ИЛИ в направлении x, ИЛИ в направлении y
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Проверьте, не ударился ли луч об стену
            if (cub->p.map[mapX][mapY] == '1')
                hit = 1;
        }
        //Вычислите расстояние, проецируемое на направление камеры (Евклидово расстояние даст эффект рыбьего глаза!)
        if (side == 0)
            perpWallDist = (mapX - cub->plr.y + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - cub->plr.x + (1 - stepY) / 2) / rayDirY;

        //Вычислите высоту линии для рисования на экране
        int lineHeight = (int)(cub->p.resolution_l / perpWallDist);

        //вычислите самый низкий и самый высокий пиксель для заполнения текущей полосы
        int drawStart = - lineHeight / 2 + cub->p.resolution_l / 2;

        if (drawStart < 0)
            drawStart = 0;

        int drawEnd = lineHeight / 2 + cub->p.resolution_l / 2;

        if (drawEnd >= cub->p.resolution_l)
            drawEnd = cub->p.resolution_l - 1;

        int y = drawStart;
        while (y++ < drawEnd)
            my_mlx_pixel_put(&cub->data, x, y, 0x00038CFC);
    }
    mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->data.img, 0, 0);
}

/*
** key_hook: взаимодействие с клавиатурой.
*/

static	int		key_hook(int keycode, t_cub *cub)
{
    mlx_destroy_image(cub->mlx, cub->data.img);
	if (keycode == 53)
		close_win(cub);
	 //модификаторы скорости
    double moveSpeed = 0.1; //постоянное значение выражается в квадратах в секунду
    double rotSpeed = 0.1; //постоянное значение находится в радианах/секунде

    //двигайтесь вперед, если перед вами нет стены
    if(keycode == 13)
    {
        printf("1 cub->plr.y: %f\n", cub->plr.y);
        if(cub->p.map[(int)(cub->plr.y + cub->plr.dirY * moveSpeed)][(int)(cub->plr.x)] == '*')
            cub->plr.y += cub->plr.dirY * moveSpeed;
        if(cub->p.map[(int)(cub->plr.y)][(int)(cub->plr.x + cub->plr.dirX * moveSpeed)] == '*')
            cub->plr.x += cub->plr.dirX * moveSpeed;
        printf("1 cub->plr.y: %f\n", cub->plr.y);
    }
    //движение назад, если за вами нет стены
    if(keycode == 1)
    {
        printf("2 cub->plr.y: %f\n", cub->plr.y);
        printf("2 cub->plr.x: %f\n", cub->plr.x);
        printf("2 plr.dirY: %f\n", cub->plr.dirY);
        if(cub->p.map[(int)(cub->plr.y - cub->plr.dirY * moveSpeed)][(int)(cub->plr.x)] == '*')
            cub->plr.y -= cub->plr.dirY * moveSpeed;
        if(cub->p.map[(int)(cub->plr.y)][(int)(cub->plr.x - cub->plr.dirX * moveSpeed)] == '*')
            cub->plr.x -= cub->plr.dirX * moveSpeed;
        printf("2 plr.dirY: %f\n", cub->plr.dirY);
        printf("2 cub->plr.y: %f\n", cub->plr.y);
        printf("2 cub->plr.x: %f\n", cub->plr.x);
    }
    //поворот вправо
    if(keycode == 124)
    {
        //как направление камеры, так и плоскость камеры должны быть повернуты
        double oldDirX = cub->plr.dirX;
        cub->plr.dirX = cub->plr.dirX * cos(-rotSpeed) - cub->plr.dirY * sin(-rotSpeed);
        cub->plr.dirY = oldDirX * sin(-rotSpeed) + cub->plr.dirY * cos(-rotSpeed);
        double oldPlaneX = cub->plr.planeX;
        cub->plr.planeX = cub->plr.planeX * cos(-rotSpeed) - cub->plr.planeY * sin(-rotSpeed);
        cub->plr.planeY = oldPlaneX * sin(-rotSpeed) + cub->plr.planeY * cos(-rotSpeed);
    }
    //поварот влево
    if(keycode == 123)
    {
        //как направление камеры, так и плоскость камеры должны быть повернуты
        double oldDirX = cub->plr.dirX;
        cub->plr.dirX = cub->plr.dirX * cos(rotSpeed) - cub->plr.dirY * sin(rotSpeed);
        cub->plr.dirY = oldDirX * sin(rotSpeed) + cub->plr.dirY * cos(rotSpeed);
        double oldPlaneX = cub->plr.planeX;
        cub->plr.planeX = cub->plr.planeX * cos(rotSpeed) - cub->plr.planeY * sin(rotSpeed);
        cub->plr.planeY = oldPlaneX * sin(rotSpeed) + cub->plr.planeY * cos(rotSpeed);
    }
    print_map(cub);
    printf("You put: %d\n", keycode);
	return (0);
}

/*
** start_cub3d: запуск окна, работа в 3D.
*/

void    start_cub3d(t_cub *cub)
{
    //начальный расположение игрока
    cub->plr.x = cub->p.playr_x;
    cub->plr.y = cub->p.playr_y;

    //начальный вектор направления
    cub->plr.dirX = -1;
    cub->plr.dirY = 0;
    cub->plr.planeX = 0;
    cub->plr.planeY = 0.66; //2d рейкастинг версия плоскости камеры

    cub->mlx = mlx_init();
    cub->mlx_win = mlx_new_window(cub->mlx, cub->p.resolution_w, cub->p.resolution_l, "cub3d");

    print_map(cub);

    mlx_hook(cub->mlx_win, 2, 1L<<0, key_hook, cub);
	mlx_hook(cub->mlx_win, 17, 1L<<0, close_win, cub);
    mlx_loop(cub->mlx);
}
