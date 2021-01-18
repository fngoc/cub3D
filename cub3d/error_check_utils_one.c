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

void	check_all_data(t_parser *p)
{
	if (p->resolution_l == 0 || p->resolution_w == 0
	|| ft_strlen(p->north_texture) == 0
	|| ft_strlen(p->south_texture) == 0 || ft_strlen(p->west_texture) == 0
	|| ft_strlen(p->east_texture) == 0 || ft_strlen(p->sprite_texture) == 0
	|| p->floore_flag != 1 || p->ceilling_flag != 1)
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

void	check_c(t_parser *p)
{
	if ((p->ceilling_r > 255 || p->ceilling_r < 0) ||
	(p->ceilling_g > 255 || p->ceilling_g < 0) ||
	(p->ceilling_b > 255 || p->ceilling_b < 0))
		error("ERROR: Not a valid ceilling color");
	p->ceilling_flag = 1;
}

/*
** check_F: проверка floore.
*/

void	check_f(t_parser *p)
{
	if ((p->floore_r > 255 || p->floore_r < 0) ||
	(p->floore_g > 255 || p->floore_g < 0) ||
	(p->floore_b > 255 || p->floore_b < 0))
		error("ERROR: Not a valid floor color");
	p->floore_flag = 1;
}

/*
** check_R: проверка resolution.
*/

void	check_r(t_parser *p)
{
	if (p->resolution_w < 0 || p->resolution_l < 0)
		error("ERROR: Not a valid resolution");
	if (p->resolution_w > 5120 || p->resolution_l > 2880)
		error("ERROR: The screen resolution is too high");
}
