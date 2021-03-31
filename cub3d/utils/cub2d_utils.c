#include "../cub3d.h"

/*
** print_player_cub: печать персонажа квадратного.
*/

void	print_player_cub(t_cub *cub)
{
	int y_tmp;
	int x_tmp;

	y_tmp = 0;
	while (y_tmp++ < SCALE)
	{
		x_tmp = 0;
		while (x_tmp++ < SCALE)
		{
			my_mlx_pixel_put(&cub->data, cub->plr.x
			+ y_tmp, cub->plr.y + x_tmp, 0x00F54242);
		}
	}
}

/*
** print_player_pix: печать персонажа в пиксель
*/

void	print_player_pix(t_cub *cub)
{
	my_mlx_pixel_put(&cub->data, cub->plr.x, cub->plr.y, 0x0000FF00);
}

/*
** print_rays: печать лучей.
*/

void	print_rays(t_cub *cub)
{
	t_plr	ray;

	ray = cub->plr;
	ray.start = ray.dir - (PI / 4);
	ray.end = ray.dir + (PI / 4);
	while (ray.start <= ray.end)
	{
		ray.x = cub->plr.x;
		ray.y = cub->plr.y;
		while (cub->p.map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(ray.start);
			ray.y += sin(ray.start);
			my_mlx_pixel_put(&cub->data, ray.x, ray.y, 0x0000FF00);
		}
		ray.start += (PI / 2) / 90;
	}
}

/*
** print_ray: печать луча.
*/

void	print_ray(t_cub *cub)
{
	t_plr	ray;

	ray = cub->plr;
	while (cub->p.map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
	{
		ray.x += cos(ray.dir);
		ray.y += sin(ray.dir);
		my_mlx_pixel_put(&cub->data, ray.x, ray.y, 0x990099);
	}
}

/*
** print_step: печать отмаштабированых кубов для карты.
*/

void	print_step(t_cub *cub, int color)
{
	int y_tmp;
	int x_tmp;

	y_tmp = 0;
	while (y_tmp++ < SCALE)
	{
		x_tmp = 0;
		while (x_tmp++ < SCALE)
			my_mlx_pixel_put(&cub->data, cub->point.x
				+ y_tmp, cub->point.y + x_tmp, color);
	}
}
