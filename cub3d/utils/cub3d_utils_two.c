/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:10:42 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/04 23:06:31 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** side_world_norm: функция для нормы.
*/

void	side_world_norm(t_norm_print_map *n, t_cub *cub, int *x, int *y)
{
	n->tex_y = (int)n->tex_pos & (TEXHEIGHT - 1);
	n->tex_pos += n->step;
	if (n->side == 0)
	{
		if (n->step_x > 0)
			my_mlx_pixel_put(&cub->data, *x, *y,
			get_pixel(&cub->t_s, n->tex_x, n->tex_y));
		else
			my_mlx_pixel_put(&cub->data, *x, *y,
			get_pixel(&cub->t_n, n->tex_x, n->tex_y));
	}
	else
	{
		if (n->step_y > 0)
			my_mlx_pixel_put(&cub->data, *x, *y,
			get_pixel(&cub->t_e, n->tex_x, n->tex_y));
		else
			my_mlx_pixel_put(&cub->data, *x, *y,
			get_pixel(&cub->t_w, n->tex_x, n->tex_y));
	}
}

/*
** set_sprite: функция для нормы.
*/

void	set_sprite(t_cub *cub, t_norm_print_sprite *s, int *i)
{
	s->sprite_x = cub->x[*i] - cub->plr.x;
	s->sprite_y = cub->y[*i] - cub->plr.y;
	s->inv_det = 1.0 / (cub->plr.plane_x * cub->plr.dir_y
					- cub->plr.dir_x * cub->plr.plane_y);
	s->transform_x = s->inv_det * (cub->plr.dir_y * s->sprite_x
								- cub->plr.dir_x * s->sprite_y);
	s->transform_y = s->inv_det * (-cub->plr.plane_y * s->sprite_x
								+ cub->plr.plane_x * s->sprite_y);
	s->sprite_screen_x = (int)((cub->p.res_w / 2)
		* (1 + s->transform_x / s->transform_y));
	s->sprite_height = abs((int)(cub->p.res_l / (s->transform_y)));
	s->draw_start_y = -s->sprite_height / 2 + cub->p.res_l / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + cub->p.res_l / 2;
	if (s->draw_end_y >= cub->p.res_l)
		s->draw_end_y = cub->p.res_l - 1;
	s->sprite_width = abs((int)(cub->p.res_l / (s->transform_y)));
	s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_end_x >= cub->p.res_w)
		s->draw_end_x = cub->p.res_w - 1;
}

/*
** print_sprite_norm: функция для нормы..
*/

void	print_sprite_norm(t_cub *cub, t_norm_print_sprite *s,
										int *y, int *stripe)
{
	*y = s->draw_start_y;
	while (*y < s->draw_end_y)
	{
		s->d = (*y) * 256 - cub->p.res_l
		* 128 + s->sprite_height * 128;
		s->tex_y = ((s->d * TEXHEIGHT) / s->sprite_height) / 256;
		s->color = get_pixel(&cub->t_spr, s->tex_x, s->tex_y);
		if (s->color != 0)
			my_mlx_pixel_put(&cub->data, *stripe, *y, s->color);
		(*y)++;
	}
}
