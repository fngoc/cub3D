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
	t_cub3d		cub3d;

	check_errors_arg(argc, argv);
	parser(argv, &cub3d.p);

	/* Печать даннх */
	printf("R: %d|\nR: %d|\nNO: %s|\nSO: %s|\nWE: %s|\nEA: %s|\nS: %s|\nfloore_r: %d|\nfloore_g: %d|\nfloore_B: %d|\nceilling_r: %d|\nceilling_g: %d|\nceilling_b: %d|\nsize_map: %d|\n", cub3d.p.resolution_w, cub3d.p.resolution_l, cub3d.p.north_texture, cub3d.p.south_texture, cub3d.p.west_texture, cub3d.p.east_texture, cub3d.p.sprite_texture, cub3d.p.floore_r, cub3d.p.floore_g, cub3d.p.floore_b, cub3d.p.ceilling_r, cub3d.p.ceilling_g, cub3d.p.ceilling_b, cub3d.p.size_map);

	/* Печать индекса игрока */
	printf("Player is here: y:%d x:%d\n", cub3d.p.playr_y, cub3d.p.playr_x);

	/* Печать карты */
	int i = -1;
	while (cub3d.p.map[++i])
		ft_putendl_fd(cub3d.p.map[i], 1);

	start(&cub3d);
	free(&cub3d);
	return (0);
}
