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
	{
		ft_putstr_fd("Error\nWas set not all edificatory or ", 1);
		error("are there repetitions", cub);
	}
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
			error("Error\nA space was found in color", cub);
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
		error("Error\nNot a valid ceilling color", cub);
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
		error("Error\nNot a valid floor color", cub);
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
		error("Error\nNot a valid resolution", cub);
	if (cub->p.res_w > width || cub->p.res_l > height)
	{
		cub->p.res_w = width;
		cub->p.res_l = height;
	}
}
