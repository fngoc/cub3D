/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 23:54:23 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/06 20:31:32 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** malloc_arrays: выделение памяти под масив спрайтов.
*/

static	void		malloc_arrays(t_cub *cub)
{
	if (!(cub->x = malloc(sizeof(float) * cub->p.coll_sprite)))
		error("Error\nNo memory allocated", cub);
	if (!(cub->y = malloc(sizeof(float) * cub->p.coll_sprite)))
		error("Error\nNo memory allocated", cub);
	if (!(cub->dist = malloc(sizeof(float) * cub->p.coll_sprite)))
		error("Error\nNo memory allocated", cub);
	if (!(cub->close_sprite = malloc(sizeof(double) * cub->p.res_w)))
		error("Error\nNo memory allocated", cub);
}

/*
** print_sprite: печать спрайта.
*/

static	void		print_sprite(t_cub *cub)
{
	t_norm_print_sprite	s;
	int					i;
	int					y;
	int					stripe;

	i = -1;
	while (++i < cub->p.coll_sprite)
	{
		set_sprite(cub, &s, &i);
		stripe = s.draw_start_x;
		while (stripe < s.draw_end_x)
		{
			s.tex_x = (int)(256 * (stripe - (-s.sprite_width / 2
			+ s.sprite_screen_x)) * TEXWIDTH / s.sprite_width) / 256;
			if (s.transform_y > 0 && stripe > 0 && stripe < cub->p.res_w
						&& s.transform_y < cub->close_sprite[stripe])
			{
				print_sprite_norm(cub, &s, &y, &stripe);
			}
			++stripe;
		}
	}
}

/*
** print_map: печать карты.
*/

static	void		print_map(t_cub *cub)
{
	t_norm_print_map	n;
	int					x;
	int					y;

	cub->data.img = mlx_new_image(cub->mlx, cub->p.res_w, cub->p.res_l);
	cub->data.addr = mlx_get_data_addr(cub->data.img,
	&cub->data.bits_per_pixel, &cub->data.line_length, &cub->data.endian);
	x = -1;
	while (++x < cub->p.res_w)
	{
		set_cam_ray_mapxy(&n, &x, cub);
		calc_step_start(&n, cub);
		while (n.hit == 0)
			check_hit(&n, cub);
		calc_more(&n, cub, &x);
		n.step = 1.0 * TEXHEIGHT / n.line_height;
		n.tex_pos = (n.draw_start - cub->p.res_l
				/ 2 + n.line_height / 2) * n.step;
		y = -1;
		while (++y < cub->p.res_l)
			side_world(&n, cub, &x, &y);
	}
	sort_sprite(cub);
	print_sprite(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->data.img, 0, 0);
}

/*
** key_hook: взаимодействие с клавиатурой.
*/

static	int			key_hook(int keycode, t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->data.img);
	if (keycode == 13)
		move_up(cub, 0.1);
	if (keycode == 1)
		move_back(cub, 0.1);
	if (keycode == 0)
		move_left(cub, 0.1);
	if (keycode == 2)
		move_right(cub, 0.1);
	if (keycode == 124)
		turn_right(cub, 0.1);
	if (keycode == 123)
		turn_left(cub, 0.1);
	if (keycode == 48)
		system("afplay ./sounds/minecraft-death-sound.mp3 & ");
	if (keycode == 53)
		close_win(cub);
	print_map(cub);
	return (0);
}

/*
** start_cub3d: запуск окна, работа в 3D.
*/

void				start_cub3d(t_cub *cub, int argc)
{
	cub->plr.y = (double)cub->p.playr_y + 0.5;
	cub->plr.x = (double)cub->p.playr_x + 0.5;
	cub->p.coll_sprite = counting_sprites(cub);
	malloc_arrays(cub);
	save_position_sprites(cub);
	set_dir_plr(cub);
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, cub->p.res_w,
									cub->p.res_l, "cub3d");
	get_sprite(cub);
	print_map(cub);
	if (argc == 3)
		screenshot(cub);
	else
	{
		system("afplay ./sounds/C418-Door.mp3 & ");
		mlx_hook(cub->mlx_win, 2, 1L << 0, key_hook, cub);
		mlx_hook(cub->mlx_win, 17, 1L << 0, close_win, cub);
		mlx_loop(cub->mlx);
	}
}
