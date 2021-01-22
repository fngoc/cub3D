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
** my_mlx_pixel_put: измененная функция mlx_pixel_put
** для увеличения скорости работы.
*/

static	void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

/*
** print_player: печать персонажа.
*/

// static	void	print_player(t_cub3d *cub3d)
// {
// 	float y_tmp;
// 	float x_tmp;

// 	y_tmp = 0;
// 	while (y_tmp++ < SCALE)
// 	{
// 		x_tmp = 0;
// 		while (x_tmp++ < SCALE)
// 			my_mlx_pixel_put(&cub3d->data, cub3d->plr.x * SCALE + x_tmp, cub3d->plr.y * SCALE + y_tmp, 0x00F54242);
// 	}
// }

static	void	print_player(t_cub3d *cub3d)
{
	
	while (cub3d->p.map[(int)(cub3d->plr.y / SCALE)][(int)(cub3d->plr.x / SCALE)] != '1')
	{
		cub3d->plr.x += cos(cub3d->p.dir);
		cub3d->plr.y += sin(cub3d->p.dir);
		my_mlx_pixel_put(&cub3d->data, cub3d->plr.x, cub3d->plr.y, 0x00F54242);
	}
}

/*
** print_step: печать больших пикселей.
*/

static	void	print_step(t_cub3d *cub3d, int color)
{
	int y_tmp;
	int x_tmp;

	y_tmp = 0;
	while (y_tmp++ < SCALE)
	{
		x_tmp = 0;
		while (x_tmp++ < SCALE)
			my_mlx_pixel_put(&cub3d->data, cub3d->point.x + y_tmp, cub3d->point.y + x_tmp, color);
	}
}

/*
** print_map: печать карты с игроком.
*/

static	void	print_map(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = -1;
	cub3d->point.x = 0;
	cub3d->point.y = 0;
	cub3d->data.img = mlx_new_image(cub3d->mlx, cub3d->p.resolution_w, cub3d->p.resolution_l);
    cub3d->data.addr = mlx_get_data_addr(cub3d->data.img, &cub3d->data.bits_per_pixel, &cub3d->data.line_length, &cub3d->data.endian);
	while (++i != cub3d->p.size_map)
	{
		j = 0;
		while (cub3d->p.map[i][j] != '\0')
		{
			if (cub3d->p.map[i][j] == '1')
				print_step(cub3d, 0x00FFFFFF);
			else if (i == cub3d->p.playr_y && j == cub3d->p.playr_x)
				print_step(cub3d, 0x006300FD);
			else if (cub3d->p.map[i][j] == '*' || cub3d->p.map[i][j] == '0')
				print_step(cub3d, 0x006300FD);
			++j;
			cub3d->point.x += SCALE;
		}
		cub3d->point.x = 0;
		cub3d->point.y += SCALE;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->data.img, 50, 50);
}

/*
** close_win: закрытие окна и выход из программы.
*/

static	int	close_win(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->mlx, cub3d->mlx_win);
	exit(1);
	return (0);
}

/*
** key_hook: взаимодействие с клавиатурой.
*/

static	int		key_hook(int keycode, t_cub3d *cub3d)
{
	// if ((cub3d->p.map[(int)cub3d->plr.y][(int)cub3d->plr.x]) == '1')
	mlx_clear_window(cub3d->mlx, cub3d->mlx_win);
	if (keycode == 126)
		cub3d->plr.y -= 0.1;
	if (keycode == 125)
		cub3d->plr.y += 0.1;
	if (keycode == 123)
		cub3d->plr.x -= 0.1;
	if (keycode == 124)
		cub3d->plr.x += 0.1;
	if (keycode == 53)
		close_win(cub3d);
	print_map(cub3d);
	print_player(cub3d);
    printf("You put: %d\n", keycode);
	return (0);
}

/*
** start: запуск окна.
*/

void			start(t_cub3d *cub3d)
{
	cub3d->plr.y = 200;
	cub3d->plr.x = 200;
	cub3d->mlx = mlx_init();
    cub3d->mlx_win = mlx_new_window(cub3d->mlx, cub3d->p.resolution_w, cub3d->p.resolution_l, "cub3d");
	print_map(cub3d);
	print_player(cub3d);
	mlx_hook(cub3d->mlx_win, 2, 1L<<0, key_hook, cub3d);
	mlx_hook(cub3d->mlx_win, 17, 1L<<0, close_win, cub3d);
	mlx_loop(cub3d->mlx);
}
