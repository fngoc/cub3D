/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_plr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:04:33 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/03 13:57:51 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** set_dir_plr_norm: функция для нормы.
*/

static	void	set_dir_plr_norm(t_cub *cub)
{
	if (cub->plr.dir_symbol == 'W')
	{
		cub->plr.dirY = 0;
		cub->plr.dirX = -1;
		cub->plr.planeY = -0.66;
		cub->plr.planeX = 0;
	}
	else if (cub->plr.dir_symbol == 'E')
	{
		cub->plr.dirY = 0;
		cub->plr.dirX = 1;
		cub->plr.planeY = 0.66;
		cub->plr.planeX = 0;
	}
}

/*
** set_dir_plr: установка направления персонажа.
*/

void			set_dir_plr(t_cub *cub)
{
	if (cub->plr.dir_symbol == 'N')
	{
		cub->plr.dirY = -1;
		cub->plr.dirX = 0;
		cub->plr.planeY = 0;
		cub->plr.planeX = 0.66;
	}
	else if (cub->plr.dir_symbol == 'S')
	{
		cub->plr.dirY = 1;
		cub->plr.dirX = 0;
		cub->plr.planeY = 0;
		cub->plr.planeX = -0.66;
	}
	else
		set_dir_plr_norm(cub);
}
