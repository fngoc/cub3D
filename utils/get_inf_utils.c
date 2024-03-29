#include "../cub3d.h"

/*
** get_floore: получить floore с проверкой.
*/

void	get_floore(char *tmp, t_cub *cub)
{
	if (ft_isdigit(*tmp))
		cub->p.floore_r = ft_atoi(tmp);
	else
		error("Error\nNot set floore_r", cub);
	tmp += ft_digit_num(cub->p.floore_r) + 1;
	if (ft_isdigit(*tmp))
		cub->p.floore_g = ft_atoi(tmp);
	else
		error("Error\nNot set floore_g", cub);
	tmp += ft_digit_num(cub->p.floore_g) + 1;
	if (ft_isdigit(*tmp))
		cub->p.floore_b = ft_atoi(tmp);
	else
		error("Error\nNot set floore_b", cub);
}

/*
** get_ceilling: получить ceilling с проверкой.
*/

void	get_ceilling(char *tmp, t_cub *cub)
{
	if (ft_isdigit(*tmp))
		cub->p.ceilling_r = ft_atoi(tmp);
	else
		error("Error\nNot set ceilling_r", cub);
	tmp += ft_digit_num(cub->p.ceilling_r) + 1;
	if (ft_isdigit(*tmp))
		cub->p.ceilling_g = ft_atoi(tmp);
	else
		error("Error\nNot set ceilling_g", cub);
	tmp += ft_digit_num(cub->p.ceilling_g) + 1;
	if (ft_isdigit(*tmp))
		cub->p.ceilling_b = ft_atoi(tmp);
	else
		error("Error\nNot set ceilling_b", cub);
}
