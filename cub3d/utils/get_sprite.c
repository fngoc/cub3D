/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:48:51 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/03 16:48:12 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** get_sprite_norm: функция для нормы.
*/

void	get_sprite_norm(t_cub *cub)
{
	int width;
	int height;

	if (!(cub->t_spr.img = mlx_xpm_file_to_image(cub->mlx,
									cub->p.spr_tex, &width, &height)))
		error("ERROR: No texture found for the sprite", cub);
	cub->t_spr.addr = mlx_get_data_addr(cub->t_spr.img,
	&cub->t_spr.bits_per_pixel, &cub->t_spr.line_length, &cub->t_spr.endian);
}

/*
** get_sprite: схватываем текстуры и спрайт.
*/

void	get_sprite(t_cub *cub)
{
	int width;
	int height;

	if (!(cub->t_n.img = mlx_xpm_file_to_image(cub->mlx,
						cub->p.nor_tex, &width, &height)))
		error("ERROR: No texture found for North", cub);
	cub->t_n.addr = mlx_get_data_addr(cub->t_n.img, &cub->t_n.bits_per_pixel,
									&cub->t_n.line_length, &cub->t_n.endian);
	if (!(cub->t_s.img = mlx_xpm_file_to_image(cub->mlx,
						cub->p.sou_tex, &width, &height)))
		error("ERROR: No texture found for the South", cub);
	cub->t_s.addr = mlx_get_data_addr(cub->t_s.img, &cub->t_s.bits_per_pixel,
					&cub->t_s.line_length, &cub->t_s.endian);
	if (!(cub->t_w.img = mlx_xpm_file_to_image(cub->mlx,
						cub->p.wes_tex, &width, &height)))
		error("ERROR: No texture found for the West", cub);
	cub->t_w.addr = mlx_get_data_addr(cub->t_w.img, &cub->t_w.bits_per_pixel,
									&cub->t_w.line_length, &cub->t_w.endian);
	if (!(cub->t_e.img = mlx_xpm_file_to_image(cub->mlx,
						cub->p.eas_tex, &width, &height)))
		error("ERROR: No texture found for the East", cub);
	cub->t_e.addr = mlx_get_data_addr(cub->t_e.img, &cub->t_e.bits_per_pixel,
									&cub->t_e.line_length, &cub->t_e.endian);
	get_sprite_norm(cub);
}
