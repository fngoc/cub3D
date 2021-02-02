/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir_plr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:04:33 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/02 13:07:06 by fngoc            ###   ########.fr       */
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
		cub->plr.dirY = 0.029199;
		cub->plr.dirX = -0.999574;
		cub->plr.planeY = -0.659719;
		cub->plr.planeX = -0.019272;
	}
	else if (cub->plr.dir_symbol == 'E')
	{
		cub->plr.dirY = 0.029200;
		cub->plr.dirX = 0.999574;
		cub->plr.planeY = 0.659719;
		cub->plr.planeX = -0.019272;
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
		cub->plr.dirY = 0.998295;
		cub->plr.dirX = 0.058374;
		cub->plr.planeY = 0.038527;
		cub->plr.planeX = -0.658875;
	}
	else
		set_dir_plr_norm(cub);
}
