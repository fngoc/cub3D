/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 23:54:23 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/04 11:25:27 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** malloc_arrays: выделение памяти под масив спрайтов.
*/

static void malloc_arrays(t_cub *cub)
{
    if (!(cub->x = malloc(sizeof(float) * cub->p.coll_sprite)))
        error("ERROR: No memory allocated", cub);
    if (!(cub->y = malloc(sizeof(float) * cub->p.coll_sprite)))
        error("ERROR: No memory allocated", cub);
    if (!(cub->dist = malloc(sizeof(float) * cub->p.coll_sprite)))
        error("ERROR: No memory allocated", cub);
    if (!(cub->close_sprite = malloc(sizeof(double) * cub->p.res_w)))
        error("ERROR: No memory allocated", cub);
}

/*
** print_sprite: печать спрайта.
*/

static void print_sprite(t_cub *cub)
{
    int i;

    i = -1;
    while (++i < cub->p.coll_sprite)
    {
        //перевести положение спрайта относительно камеры
        double spriteX = cub->x[i] - cub->plr.x;
        double spriteY = cub->y[i] - cub->plr.y;
    
        //требуется для правильного умножения матриц
        double invDet = 1.0 / (cub->plr.planeX * cub->plr.dirY - cub->plr.dirX * cub->plr.planeY);

        double transformX = invDet * (cub->plr.dirY * spriteX - cub->plr.dirX * spriteY);

        //это на самом деле глубина внутри экрана, то, что Z есть в 3D
        double transformY = invDet * (-cub->plr.planeY * spriteX + cub->plr.planeX * spriteY); 

        int spriteScreenX = (int)((cub->p.res_w / 2) * (1 + transformX / transformY));

        //вычислите высоту спрайта на экране
        int spriteHeight = abs((int)(cub->p.res_l / (transformY))); //с помощью transformY' вместо реального расстояния предотвращает рыбий глаз
        //вычислите самый низкий и самый высокий пиксель для заполнения текущей полосы
        int drawStartY = -spriteHeight / 2 + cub->p.res_l / 2;
        if (drawStartY < 0)
            drawStartY = 0;
        int drawEndY = spriteHeight / 2 + cub->p.res_l / 2;
        if (drawEndY >= cub->p.res_l)
            drawEndY = cub->p.res_l - 1;

        //вычислить ширину спрайта
        int spriteWidth = abs((int)(cub->p.res_l / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0) drawStartX = 0;
            int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= cub->p.res_w)
            drawEndX = cub->p.res_w - 1;

        //петля через каждую вертикальную полосу спрайта на экране
        int stripe;
        int y;

        stripe = drawStartX;
        while (stripe < drawEndX)
        {
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXWIDTH / spriteWidth) / 256;
            if (transformY > 0 && stripe > 0 && stripe < cub->p.res_w && transformY < cub->close_sprite[stripe])
            {
                y = drawStartY;
                while (y < drawEndY) //для каждого пикселя текущей полосы
                {
                    int d = (y) * 256 - cub->p.res_l * 128 + spriteHeight * 128;
                    int texY = ((d * TEXHEIGHT) / spriteHeight) / 256;
                    int color = get_pixel(&cub->t_spr, texX, texY);
                    if (color != 0)
                    my_mlx_pixel_put(&cub->data, stripe, y, color);
                    y++;
                }
            }
            ++stripe;
        }
    }
}

/*
** print_map: печать карты.
*/

static  void  print_map(t_cub *cub)
{
    cub->data.img = mlx_new_image(cub->mlx, cub->p.res_w, cub->p.res_l);
    cub->data.addr = mlx_get_data_addr(cub->data.img, &cub->data.bits_per_pixel, &cub->data.line_length, &cub->data.endian);

    int x = -1;
    while (++x < cub->p.res_w)
    {
        //вычислить положение и направление луча
        double cameraX = 2 * x / (double)cub->p.res_w - 1; //x-coordinate in camera space
        double rayDirX = cub->plr.dirY + cub->plr.planeY * cameraX;
        double rayDirY = cub->plr.dirX + cub->plr.planeX * cameraX;

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

        int hit = 0; //был ли удар об стену?
        int side; //была ли поражена стена NS или WE?

        //вычислить шаг и начальную сторону sideDist
        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (cub->plr.y - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - cub->plr.y) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (cub->plr.x - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - cub->plr.x) * deltaDistY;
        }
        //проанализировать DDA
        while (hit == 0)
        {
            //переход к следующему квадрату карты, ИЛИ в направлении x, ИЛИ в направлении y
            if(sideDistX < sideDistY)
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
            if(cub->p.map[mapX][mapY] == '1')
                hit = 1;
        }
        //Вычислите расстояние, проецируемое на направление камеры (Евклидово расстояние даст эффект рыбьего глаза)
        if (side == 0)
            perpWallDist = (mapX - cub->plr.y + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - cub->plr.x + (1 - stepY) / 2) / rayDirY;
        cub->close_sprite[x] = perpWallDist;
        //Вычислите высоту линии для рисования на экране
        int lineHeight = (int)(cub->p.res_l / perpWallDist);

        //вычислите самый низкий и самый высокий пиксель для заполнения текущей полосы
        int drawStart = -lineHeight / 2 + cub->p.res_l / 2;
        if (drawStart < 0)
            drawStart = 0;

        int drawEnd = lineHeight / 2 + cub->p.res_l / 2;
        if (drawEnd >= cub->p.res_l)
            drawEnd = cub->p.res_l - 1;

        //вычислите значение wallxoven
        double wallX; //куда именно ударилась стена
        if (side == 0)
            wallX = cub->plr.x + perpWallDist * rayDirY;
        else
            wallX = cub->plr.y + perpWallDist * rayDirX;
        wallX -= floor((wallX));
    
        //координата x на текстуре
        int texX = (int)(wallX * (double)(TEXWIDTH));
        if (side == 0 && rayDirX > 0)
            texX = TEXWIDTH - texX - 1;
        if (side == 1 && rayDirY < 0)
            texX = TEXWIDTH - texX - 1;

        // Насколько увеличить координату текстуры на пиксель экрана
        double step = 1.0 * TEXHEIGHT / lineHeight;
        // Начальная координата текстуры
        double texPos = (drawStart - cub->p.res_l / 2 + lineHeight / 2) * step;  

        int y = -1;
        while (++y < cub->p.res_l)
        {
            if (y < drawStart)
                my_mlx_pixel_put(&cub->data, x, y, create_rgb(cub->p.ceilling_r, cub->p.ceilling_g, cub->p.ceilling_b));
            if (y >= drawStart && y <= drawEnd)
            {
                int texY = (int)texPos & (TEXHEIGHT - 1);
                texPos += step;
                if (side == 0) //N и S
                    if (stepX > 0) //S
                        my_mlx_pixel_put(&cub->data, x, y, get_pixel(&cub->t_s, texX, texY));
                    else //N
                        my_mlx_pixel_put(&cub->data, x, y, get_pixel(&cub->t_n, texX, texY));
                else //W и E
                    if (stepY > 0) //E
                        my_mlx_pixel_put(&cub->data, x, y, get_pixel(&cub->t_e, texX, texY));
                    else //W
                        my_mlx_pixel_put(&cub->data, x, y, get_pixel(&cub->t_w, texX, texY));
            }
            if (y > drawEnd && y < cub->p.res_l)
                 my_mlx_pixel_put(&cub->data, x, y, create_rgb(cub->p.floore_r, cub->p.floore_g, cub->p.floore_b));
        }
    }
    sort_sprite(cub);
    print_sprite(cub);
    mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->data.img, 0, 0);
}

/*
** key_hook: взаимодействие с клавиатурой.
*/

static int key_hook(int keycode, t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->data.img);
	if(keycode == 13)
		move_up(cub, 0.1);
	if(keycode == 1)
		move_back(cub, 0.1);
	if(keycode == 0)
		move_left(cub, 0.1);
	if(keycode == 2)
		move_right(cub, 0.1);
	if(keycode == 124)
		turn_right(cub, 0.1);
	if(keycode == 123)
		turn_left(cub, 0.1);
	if(keycode == 48)
		system("afplay ./sounds/minecraft-death-sound.mp3 & ");
	if (keycode == 53)
		close_win(cub);
	print_map(cub);
	return (0);
}

/*
** start_cub3d: запуск окна, работа в 3D.
*/

void  start_cub3d(t_cub *cub, int argc)
{
	cub->plr.y = (double)cub->p.playr_y + 0.5;
	cub->plr.x = (double)cub->p.playr_x + 0.5;
	cub->p.coll_sprite = counting_sprites(cub);
	malloc_arrays(cub);
	save_position_sprites(cub);
	set_dir_plr(cub);
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, cub->p.res_w, cub->p.res_l, "cub3d");
	get_sprite(cub);
	print_map(cub);
	if (argc == 3)
		screenshot(cub);
	else
	{
		system("afplay ./sounds/C418-Door.mp3 & ");
		mlx_hook(cub->mlx_win, 2, 1L<<0, key_hook, cub);
		mlx_hook(cub->mlx_win, 17, 1L<<0, close_win, cub);
		mlx_loop(cub->mlx);
	}
}
