/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 17:09:31 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/04 17:10:28 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** side_world: функция для нормы.
*/

void	side_world(t_norm_print_map *n, t_cub *cub, int *x, int *y)
{
	if (*y < n->draw_start)
		my_mlx_pixel_put(&cub->data, *x, *y,
		create_rgb(cub->p.ceilling_r, cub->p.ceilling_g, cub->p.ceilling_b));
	if (*y >= n->draw_start && *y <= n->draw_end)
		side_world_norm(n, cub, x, y);
	if (*y > n->draw_end && *y < cub->p.res_l)
		my_mlx_pixel_put(&cub->data, *x, *y,
		create_rgb(cub->p.floore_r, cub->p.floore_g, cub->p.floore_b));
}

/*
** calc_more: функция для нормы.
*/

void	calc_more(t_norm_print_map *n, t_cub *cub, int *x)
{
	if (n->side == 0)
		n->perp_wall_dist = (n->map_x - cub->plr.y
			+ (1 - n->step_x) / 2) / n->ray_dir_x;
	else
		n->perp_wall_dist = (n->map_y - cub->plr.x
			+ (1 - n->step_y) / 2) / n->ray_dir_y;
	cub->close_sprite[*x] = n->perp_wall_dist;
	n->line_height = (int)(cub->p.res_l / n->perp_wall_dist);
	n->draw_start = -n->line_height / 2 + cub->p.res_l / 2;
	if (n->draw_start < 0)
		n->draw_start = 0;
	n->draw_end = n->line_height / 2 + cub->p.res_l / 2;
	if (n->draw_end >= cub->p.res_l)
		n->draw_end = cub->p.res_l - 1;
	if (n->side == 0)
		n->wall_x = cub->plr.x + n->perp_wall_dist * n->ray_dir_y;
	else
		n->wall_x = cub->plr.y + n->perp_wall_dist * n->ray_dir_x;
	n->wall_x -= floor((n->wall_x));
	n->tex_x = (int)(n->wall_x * (double)(TEXWIDTH));
	if (n->side == 0 && n->ray_dir_x > 0)
		n->tex_x = TEXWIDTH - n->tex_x - 1;
	if (n->side == 1 && n->ray_dir_y < 0)
		n->tex_x = TEXWIDTH - n->tex_x - 1;
}

/*
** check_hit: функция для нормы.
*/

void	check_hit(t_norm_print_map *n, t_cub *cub)
{
	if (n->side_dist_x < n->side_dist_y)
	{
		n->side_dist_x += n->delta_dist_x;
		n->map_x += n->step_x;
		n->side = 0;
	}
	else
	{
		n->side_dist_y += n->delta_dist_y;
		n->map_y += n->step_y;
		n->side = 1;
	}
	if (cub->p.map[n->map_x][n->map_y] == '1')
		n->hit = 1;
}

/*
** calc_step_start: функция для нормы.
*/

void	calc_step_start(t_norm_print_map *n, t_cub *cub)
{
	if (n->ray_dir_x < 0)
	{
		n->step_x = -1;
		n->side_dist_x = (cub->plr.y - n->map_x) * n->delta_dist_x;
	}
	else
	{
		n->step_x = 1;
		n->side_dist_x = (n->map_x + 1.0 - cub->plr.y) * n->delta_dist_x;
	}
	if (n->ray_dir_y < 0)
	{
		n->step_y = -1;
		n->side_dist_y = (cub->plr.x - n->map_y) * n->delta_dist_y;
	}
	else
	{
		n->step_y = 1;
		n->side_dist_y = (n->map_y + 1.0 - cub->plr.x) * n->delta_dist_y;
	}
}

/*
** set_cam_ray_mapxy: функция для нормы.
*/

void	set_cam_ray_mapxy(t_norm_print_map *n, int *x, t_cub *cub)
{
	n->camera_x = 2 * *x / (double)cub->p.res_w - 1;
	n->ray_dir_x = cub->plr.dirY + cub->plr.planeY * n->camera_x;
	n->ray_dir_y = cub->plr.dirX + cub->plr.planeX * n->camera_x;
	n->map_x = (int)(cub->plr.y);
	n->map_y = (int)(cub->plr.x);
	n->delta_dist_x = sqrt(1 + (n->ray_dir_y * n->ray_dir_y)
							/ (n->ray_dir_x * n->ray_dir_x));
	n->delta_dist_y = sqrt(1 + (n->ray_dir_x * n->ray_dir_x)
							/ (n->ray_dir_y * n->ray_dir_y));
	n->hit = 0;
}
