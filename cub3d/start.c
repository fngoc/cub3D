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

static	void	print_step(t_data *img, t_point_print *point, int color, int flag, t_parser *p)
{
	int y_tmp;
	int x_tmp;
	
	if (flag)
	{
		p->playr_x = point->x;
		p->playr_y = point->y;
	}
	y_tmp = 0;
	while (y_tmp++ < SCALE)
	{
		x_tmp = 0;
		while (x_tmp++ < SCALE)
			my_mlx_pixel_put(img, point->x + y_tmp, point->y + x_tmp, color);
	}
}

/*
** start_map: печать карты с игроком.
*/

static	void	start_map(t_data *img, void *mlx, t_parser *p, t_point_print *point)
{
	int	i;
	int	j;

	i = -1;
	point->x = 0;
	point->y = 0;
	img->img = mlx_new_image(mlx, p->resolution_w, p->resolution_l);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	while (++i != p->size_map)
	{
		j = 0;
		while (p->map[i][j] != '\0')
		{
			if (p->map[i][j] == '1')
				print_step(img, point, 0x00FFFFFF, 0, p);
			else if (i == p->playr_y && j == p->playr_x)
				print_step(img, point, 0x00FC0330, 1, p);
			else if (p->map[i][j] == '*' || p->map[i][j] == '0')
				print_step(img, point, 0x006300FD, 0, p);
			++j;
			point->x += SCALE;
		}
		point->x = 0;
		point->y += SCALE;
	}
}

/*
** key_hook: взаимодействие с клавиатурой.
*/

// static	int		key_hook(int keycode, t_cub3d *cub3d)
// {
// 	start_map(cub3d->mlx, &cub3d->mlx, &cub3d->p, &cub3d->point);
// 	if (keycode == 126)
// 		cub3d->p.playr_y--;
// 	if (keycode == 125)
// 		cub3d->p.playr_y++;
// 	if (keycode == 123)
// 		cub3d->p.playr_x--;
// 	if (keycode == 124)
// 		cub3d->p.playr_x++;
//     printf("Hello from key_hook!\n");
// 	return (0);
// }

/*
** start: запуск окна.
*/

void			start(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
    cub3d->mlx_win = mlx_new_window(cub3d->mlx, cub3d->p.resolution_w, cub3d->p.resolution_l, "cub3d");
	start_map(&cub3d->data, cub3d->mlx, &cub3d->p, &cub3d->point);
	// mlx_key_hook(cub3d->mlx_win, key_hook, cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win, cub3d->data.img, 50, 50);
	mlx_loop(cub3d->mlx);
}
