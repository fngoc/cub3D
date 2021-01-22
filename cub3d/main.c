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
	t_cub		cub;

	check_errors_arg(argc, argv);
	parser(argv, &cub);

	/* Печать даннх */
	printf("R: %d|\nR: %d|\nNO: %s|\nSO: %s|\nWE: %s|\nEA: %s|\nS: %s|\nfloore_r: %d|\nfloore_g: %d|\nfloore_B: %d|\nceilling_r: %d|\nceilling_g: %d|\nceilling_b: %d|\nsize_map: %d|\n", cub.p.resolution_w, cub.p.resolution_l, cub.p.north_texture, cub.p.south_texture, cub.p.west_texture, cub.p.east_texture, cub.p.sprite_texture, cub.p.floore_r, cub.p.floore_g, cub.p.floore_b, cub.p.ceilling_r, cub.p.ceilling_g, cub.p.ceilling_b, cub.p.size_map);

	/* Печать индекса игрока */
	printf("Player is here: y:%d x:%d\n", cub.p.playr_y, cub.p.playr_x);

	/* Печать карты */
	int i = -1;
	while (cub.p.map[++i])
		ft_putendl_fd(cub.p.map[i], 1);

	start(&cub);
	free(&cub);
	return (0);
}
