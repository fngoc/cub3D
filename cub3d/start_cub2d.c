/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:24:31 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/19 13:05:59 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 /*
 ** print_player_cub: печать персонажа квадратного.
 */

static	void	print_player_cub(t_cub *cub)
{
	int y_tmp;
	int x_tmp;

	y_tmp = 0;
	while (y_tmp++ < SCALE)
	{
		x_tmp = 0;
		while (x_tmp++ < SCALE)
			my_mlx_pixel_put(&cub->data, cub->plr.x + y_tmp, cub->plr.y + x_tmp, 0x00F54242);
	}
}

 /*
 ** print_player_pix: печать персонажа в пиксель
 */

static	void	print_player_pix(t_cub *cub)
{
	my_mlx_pixel_put(&cub->data, cub->plr.x, cub->plr.y, 0x0000FF00);
}

 /*
 ** print_rays: печать лучей.
 */

static	void	print_rays(t_cub *cub)
{
	t_plr	ray = cub->plr;  //задаем координаты и направление луча равные координатам игрока
	ray.start = ray.dir - (PI / 4);  //начало веера лучей \|/
  	ray.end = ray.dir + (PI / 4);  //край веера лучей

 	while (ray.start <= ray.end)
	{
		ray.x = cub->plr.x;  //каждый раз возвращаемся в точку начала
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

static	void	print_ray(t_cub *cub)
{
	t_plr	ray = cub->plr;

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

static	void	print_step(t_cub *cub, int color)
{
	int y_tmp;
	int x_tmp;

	y_tmp = 0;
	while (y_tmp++ < SCALE)
	{
		x_tmp = 0;
		while (x_tmp++ < SCALE)
			my_mlx_pixel_put(&cub->data, cub->point.x + y_tmp, cub->point.y + x_tmp, color);
	}
}

 /*
 ** print_map: печать карты с игроком.
 */

static	void	print_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	cub->point.x = 0;
	cub->point.y = 0;
	cub->data.img = mlx_new_image(cub->mlx, cub->p.resolution_w, cub->p.resolution_l);
    cub->data.addr = mlx_get_data_addr(cub->data.img, &cub->data.bits_per_pixel, &cub->data.line_length, &cub->data.endian);
	while (++i != cub->p.size_map)
	{
		j = 0;
		while (cub->p.map[i][j] != '\0')
		{
			if (cub->p.map[i][j] == '1')
				print_step(cub, 0x00FFFFFF);
			else if (i == cub->p.playr_y && j == cub->p.playr_x)
				print_step(cub, 0x006300FD);
			else if (cub->p.map[i][j] == '*' || cub->p.map[i][j] == '0')
				print_step(cub, 0x006300FD);
			++j;
			cub->point.x += SCALE;
		}
		cub->point.x = 0;
		cub->point.y += SCALE;
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->data.img, 50, 50);
}

/*
** key_hook: взаимодействие с клавиатурой.
*/

static	int		key_hook(int keycode, t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->data.img);
	if (keycode == 13)
	{
		cub->plr.x += cos(cub->plr.dir);
		cub->plr.y += sin(cub->plr.dir);
	}
	if (keycode == 1)
	{
		cub->plr.x -= cos(cub->plr.dir);
		cub->plr.y -= sin(cub->plr.dir);
	}
	if (keycode == 123)
		cub->plr.dir -= 0.1;
	if (keycode == 124)
		cub->plr.dir += 0.1;
	if (keycode == 53)
		close_win(cub);
	print_map(cub);
	print_player_cub(cub);
	print_player_pix(cub);
	print_ray(cub);
	print_rays(cub);
    printf("You put: %d\n", keycode);
	return (0);
}

/*
** start_cub2d: запуск окна, работа в 2D.
*/

void			start_cub2d(t_cub *cub)
{
	cub->plr.y = cub->p.playr_y * SCALE;
	cub->plr.x = cub->p.playr_x * SCALE;
	cub->mlx = mlx_init();
    cub->mlx_win = mlx_new_window(cub->mlx, cub->p.resolution_w, cub->p.resolution_l, "cub2d");
	print_map(cub);
	print_player_cub(cub);
	print_player_pix(cub);
	print_ray(cub);
	print_rays(cub);
	mlx_hook(cub->mlx_win, 2, 1L<<0, key_hook, cub);
	mlx_hook(cub->mlx_win, 17, 1L<<0, close_win, cub);
	mlx_loop(cub->mlx);
}
