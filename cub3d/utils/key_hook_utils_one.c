/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:00:10 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/02 13:07:21 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** move_up: идти вперед.
*/

void	move_up(t_cub *cub, double s)
{
	if (cub->p.map[(int)(cub->plr.y + cub->plr.dirY * s)]
								[(int)(cub->plr.x)] == '*')
		cub->plr.y += cub->plr.dirY * s;
	if (cub->p.map[(int)(cub->plr.y)]
			[(int)(cub->plr.x + cub->plr.dirX * s)] == '*')
		cub->plr.x += cub->plr.dirX * s;
}

/*
** move_back: идти назад.
*/

void	move_back(t_cub *cub, double s)
{
	if (cub->p.map[(int)(cub->plr.y - cub->plr.dirY * s)]
								[(int)(cub->plr.x)] == '*')
		cub->plr.y -= cub->plr.dirY * s;
	if (cub->p.map[(int)(cub->plr.y)]
			[(int)(cub->plr.x - cub->plr.dirX * s)] == '*')
		cub->plr.x -= cub->plr.dirX * s;
}

/*
** move_left: идти в лево.
*/

void	move_left(t_cub *cub, double s)
{
	if (cub->p.map[(int)(cub->plr.y - cub->plr.dirX * s)]
								[(int)(cub->plr.x)] == '*')
		cub->plr.y -= cub->plr.dirX * s;
	if (cub->p.map[(int)(cub->plr.y)]
			[(int)(cub->plr.x + cub->plr.dirY * s)] == '*')
		cub->plr.x += cub->plr.dirY * s;
}

/*
** move_right: идти в право.
*/

void	move_right(t_cub *cub, double s)
{
	if (cub->p.map[(int)(cub->plr.y + cub->plr.dirX * s)]
								[(int)(cub->plr.x)] == '*')
		cub->plr.y += cub->plr.dirX * s;
	if (cub->p.map[(int)(cub->plr.y)]
			[(int)(cub->plr.x - cub->plr.dirY * s)] == '*')
		cub->plr.x -= cub->plr.dirY * s;
}

/*
** turn_right: повернуть вправо.
*/

void	turn_right(t_cub *cub, double r)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->plr.dirY;
	old_plane_x = cub->plr.planeY;
	cub->plr.dirY = cub->plr.dirY * cos(-r) - cub->plr.dirX * sin(-r);
	cub->plr.dirX = old_dir_x * sin(-r) + cub->plr.dirX * cos(-r);
	cub->plr.planeY = cub->plr.planeY * cos(-r) - cub->plr.planeX * sin(-r);
	cub->plr.planeX = old_plane_x * sin(-r) + cub->plr.planeX * cos(-r);
}
