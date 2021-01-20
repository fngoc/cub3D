/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:20:29 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/18 14:29:45 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Структура проекта: Парсер -> Карта -> Игрок ->
** Клавиатура -> Рейкастинг -> текстуры и предметы.
*/

int	main(int argc, char **argv)
{
	t_parser	p;
	t_cub3d		cub3d;

	check_errors_arg(argc, argv);
	parser(argv, &p);
	cub3d.p = p;

	/* Печать даннх */
	// printf("R: %d|\nR: %d|\nNO: %s|\nSO: %s|\nWE: %s|\nEA: %s|\nS: %s|\nfloore_r: %d|\nfloore_g: %d|\nfloore_B: %d|\nceilling_r: %d|\nceilling_g: %d|\nceilling_b: %d|\nsize_map: %d|\n", p.resolution_w, p.resolution_l, p.north_texture, p.south_texture, p.west_texture, p.east_texture, p.sprite_texture, p.floore_r, p.floore_g, p.floore_b, p.ceilling_r, p.ceilling_g, p.ceilling_b, p.size_map);

	/* Печать индекса игрока */
	// printf("Player is here: y:%d x:%d\n", cub3d.p.playr_y, cub3d.p.playr_x);

	/* Печать карты */
	// int i = -1;
	// while (cub3d.p.map[++i])
	// 	ft_putendl_fd(cub3d.p.map[i], 1);
	
	start(&cub3d);
	free(&p);
	free(&cub3d);
	return (0);
}
