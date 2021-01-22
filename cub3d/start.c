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

static	void	print_player(t_cub *cub)
{
	float y_tmp;
	float x_tmp;

	y_tmp = 0;
	while (y_tmp++ < SCALE)
	{
		x_tmp = 0;
		while (x_tmp++ < SCALE)
			my_mlx_pixel_put(&cub->data, cub->plr.x * SCALE + x_tmp, cub->plr.y * SCALE + y_tmp, 0x00F54242);
	}
}

// static	void	print_player(t_cub *cub)
// {
	
// 	while (cub->p.map[(int)(cub->plr.y / SCALE)][(int)(cub->plr.x / SCALE)] != '1')
// 	{
// 		cub->plr.x += cos(cub->p.dir);
// 		cub->plr.y += sin(cub->p.dir);
// 		my_mlx_pixel_put(&cub->data, cub->plr.x, cub->plr.y, 0x00F54242);
// 	}
// }

/*
** print_step: печать больших пикселей.
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
** close_win: закрытие окна и выход из программы.
*/

static	int	close_win(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	exit(1);
	return (0);
}

/*
** key_hook: взаимодействие с клавиатурой.
*/

static	int		key_hook(int keycode, t_cub *cub)
{
	// if ((cub->p.map[(int)cub->plr.y][(int)cub->plr.x]) == '1')
	mlx_clear_window(cub->mlx, cub->mlx_win);
	if (keycode == 126)
		cub->plr.y -= 0.1;
	if (keycode == 125)
		cub->plr.y += 0.1;
	if (keycode == 123)
		cub->plr.x -= 0.1;
	if (keycode == 124)
		cub->plr.x += 0.1;
	if (keycode == 53)
		close_win(cub);
	print_map(cub);
	print_player(cub);
    printf("You put: %d\n", keycode);
	return (0);
}

/*
** start: запуск окна.
*/

void			start(t_cub *cub)
{
	cub->plr.y = cub->p.playr_y;
	cub->plr.x = cub->p.playr_x;
	cub->mlx = mlx_init();
    cub->mlx_win = mlx_new_window(cub->mlx, cub->p.resolution_w, cub->p.resolution_l, "cub");
	print_map(cub);
	print_player(cub);
	mlx_hook(cub->mlx_win, 2, 1L<<0, key_hook, cub);
	mlx_hook(cub->mlx_win, 17, 1L<<0, close_win, cub);
	mlx_loop(cub->mlx);
}
