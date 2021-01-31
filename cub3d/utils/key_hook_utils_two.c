/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:02:30 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/30 17:02:34 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** turn_left: повернуть влево.
*/

void	turn_left(t_cub *cub, double r)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = cub->plr.dirY;
	old_plane_x = cub->plr.planeY;
	cub->plr.dirY = cub->plr.dirY * cos(r) - cub->plr.dirX * sin(r);
	cub->plr.dirX = old_dir_x * sin(r) + cub->plr.dirX * cos(r);
	cub->plr.planeY = cub->plr.planeY * cos(r) - cub->plr.planeX * sin(r);
	cub->plr.planeX = old_plane_x * sin(r) + cub->plr.planeX * cos(r);
}
