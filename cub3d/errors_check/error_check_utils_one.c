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

#include "../cub3d.h"

/*
** check_all_data: проверка на наличие всех спарсеных данных
** и что бы они встречались один раз.
*/

void	check_all_data(t_cub *cub)
{
	if (cub->p.res_l == 0 || cub->p.res_w == 0
	|| ft_strlen(cub->p.nor_tex) == 0
	|| ft_strlen(cub->p.sou_tex) == 0 || ft_strlen(cub->p.wes_tex) == 0
	|| ft_strlen(cub->p.eas_tex) == 0 || ft_strlen(cub->p.spr_tex) == 0
	|| cub->p.floore_flag != 1 || cub->p.ceilling_flag != 1)
		error("ERROR: Was set not all edificatory or are there repetitions", cub);
}

/*
** check_tab_in_r_f: проверка на пробелы в цветах.
*/

void	check_tab_in_r_f(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			error("ERROR: A space was found in color", cub);
		++i;
	}
}

/*
** check_c: проверка resolution, floore и ceilling.
*/

void	check_c(t_cub *cub)
{
	if ((cub->p.ceilling_r > 255 || cub->p.ceilling_r < 0) ||
	(cub->p.ceilling_g > 255 || cub->p.ceilling_g < 0) ||
	(cub->p.ceilling_b > 255 || cub->p.ceilling_b < 0))
		error("ERROR: Not a valid ceilling color", cub);
	cub->p.ceilling_flag = 1;
}

/*
** check_f: проверка floore.
*/

void	check_f(t_cub *cub)
{
	if ((cub->p.floore_r > 255 || cub->p.floore_r < 0) ||
	(cub->p.floore_g > 255 || cub->p.floore_g < 0) ||
	(cub->p.floore_b > 255 || cub->p.floore_b < 0))
		error("ERROR: Not a valid floor color", cub);
	cub->p.floore_flag = 1;
}

/*
** check_r: проверка resolution.
*/

void	check_r(t_cub *cub)
{
	int width;
	int height;

	mlx_get_screen_size(&cub->mlx, &width, &height);
	if (cub->p.res_w < 0 || cub->p.res_l < 0)
		error("ERROR: Not a valid resolution", cub);
	if (cub->p.res_w > width || cub->p.res_l > height)
		error("ERROR: The screen resolution is too high", cub);
}
