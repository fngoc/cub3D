/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:24:31 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/18 17:18:07 by fngoc            ###   ########.fr       */
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

// void			print_step(t_data *img, int *x, int *y, int color)
// {
// 	while (*y++ < SCALE)
// 	{
// 		*x = 0;
// 		while (*x++ < SCALE)
// 			my_mlx_pixel_put(img, *y, *x, color);
// 	}
// 	y += SCALE;
// }

/*
** start: запуск окна.
*/

void			start(void *mlx, void *mlx_win, t_parser *p)
{
	int i;
	int j;
	int x;
	int y;
	t_data img;
	int scale = 50;

	i = 0;
	x = 0;
	y = 0;
	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, p->resolution_w, p->resolution_l, "cub3d");
    img.img = mlx_new_image(mlx, p->resolution_w, p->resolution_l);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (i != p->size_map)
	{
		j = 0;
		while (p->map[i][j] != '\0')
		{
			if (p->map[i][j] == '1')
			{
				while (y++ < scale)
				{
					x = 0;
					while (x++ < scale)
						my_mlx_pixel_put(&img, x, y, 0x00FF0000);
				}
				scale += 16;
			}
			++j;
		}
		++i;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 300, 150);
	mlx_loop(mlx);
}
