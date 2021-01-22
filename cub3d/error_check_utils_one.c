/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils_one.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:16:24 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/18 12:41:01 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check_all_data: проверка на наличие всех спарсеных данных
** и что бы они встречались один раз.
*/

void	check_all_data(t_cub *cub)
{
	if (cub->p.resolution_l == 0 || cub->p.resolution_w == 0
	|| ft_strlen(cub->p.north_texture) == 0
	|| ft_strlen(cub->p.south_texture) == 0 || ft_strlen(cub->p.west_texture) == 0
	|| ft_strlen(cub->p.east_texture) == 0 || ft_strlen(cub->p.sprite_texture) == 0
	|| cub->p.floore_flag != 1 || cub->p.ceilling_flag != 1)
		error("ERROR: Was set not all edificatory or are there repetitions");
}

/*
** check_tab_in_r_f: проверка на пробелы в цветах.
*/

void	check_tab_in_r_f(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			error("ERROR: A space was found in color");
		++i;
	}
}

/*
** check_C: проверка resolution, floore и ceilling.
*/

void	check_c(t_cub *cub)
{
	if ((cub->p.ceilling_r > 255 || cub->p.ceilling_r < 0) ||
	(cub->p.ceilling_g > 255 || cub->p.ceilling_g < 0) ||
	(cub->p.ceilling_b > 255 || cub->p.ceilling_b < 0))
		error("ERROR: Not a valid ceilling color");
	cub->p.ceilling_flag = 1;
}

/*
** check_F: проверка floore.
*/

void	check_f(t_cub *cub)
{
	if ((cub->p.floore_r > 255 || cub->p.floore_r < 0) ||
	(cub->p.floore_g > 255 || cub->p.floore_g < 0) ||
	(cub->p.floore_b > 255 || cub->p.floore_b < 0))
		error("ERROR: Not a valid floor color");
	cub->p.floore_flag = 1;
}

/*
** check_R: проверка resolution.
*/

void	check_r(t_cub *cub)
{
	if (cub->p.resolution_w < 0 || cub->p.resolution_l < 0)
		error("ERROR: Not a valid resolution");
	if (cub->p.resolution_w > 5120 || cub->p.resolution_l > 2880)
		error("ERROR: The screen resolution is too high");
}
