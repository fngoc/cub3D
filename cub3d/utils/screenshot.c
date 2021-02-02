/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 00:10:58 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/02 00:19:48 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** fill_screen: заполнить скриншот.
*/

static	void	fill_screen(int fd, t_cub *cub)
{
	int i;
	int j;
	int color;

	i = cub->p.res_l;
	while (--i >= 0)
	{
		j = -1;
		while (++j < cub->p.res_w)
		{
			color = *(int*)(cub->data.addr + (i * cub->data.line_length
			+ j * (cub->data.bits_per_pixel / 8)));
			write(fd, &color, 4);
		}
	}
	exit(0);
}

/*
** screenshot_norm: функция для нормы.
*/

// void			screenshot_norm(t_cub *cub)
// {
	
// }

/*
** screenshot: сделать скриншот.
*/

void			screenshot(t_cub *cub)
{
	int		fd;
	int		all_pix;
	int		zero;
	int		pos_pix;
	int		size;
	short	plane;

	fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
	all_pix = cub->p.res_w * cub->p.res_l * 4 + 54;
	zero = 0;
	pos_pix = 54;
	plane = 1;
	size = cub->p.res_w * cub->p.res_l;
	write(fd, "BM", 2);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pix, 4);
	pos_pix = 40;
	write(fd, &pos_pix, 4);
	write(fd, &cub->p.res_w, 4);
	write(fd, &cub->p.res_l, 4);
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	all_pix = 1000;
	write(fd, &all_pix, 4);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	fill_screen(fd, cub);
}
