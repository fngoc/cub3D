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
** print_step: печать больших пикселей.
*/

void				print_step(t_data *img, t_point_print *point, int color)
{
	int y_tmp;
	int x_tmp;

	y_tmp = 0;
	while (y_tmp++ < SCALE)
	{
		x_tmp = 0;
		while (x_tmp++ < SCALE)
			my_mlx_pixel_put(img, point->x + y_tmp, point->y + x_tmp, color);
	}
}

/*
** start: запуск окна.
*/

void			start(void *mlx, void *mlx_win, t_parser *p)
{
	int				i;
	int				j;
	t_data			img;
	t_point_print	point;

	i = -1;
	point.x = 0;
	point.y = 0;
	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, p->resolution_w, p->resolution_l, "cub3d");
    img.img = mlx_new_image(mlx, p->resolution_w, p->resolution_l);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (++i != p->size_map)
	{
		j = 0;
		while (p->map[i][j] != '\0')
		{
			if (p->map[i][j] == '1')
				print_step(&img, &point, 0x00FFFFFF);
			else if (p->map[i][j] == '*' || p->map[i][j] == '0')
				print_step(&img, &point, 0x006300FD);
			++j;
			point.x += SCALE;
		}
		point.x = 0;
		point.y += SCALE;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 50, 50);
	mlx_loop(mlx);
}
