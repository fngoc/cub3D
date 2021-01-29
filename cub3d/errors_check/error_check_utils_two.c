/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:16:09 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/18 12:23:09 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** check_errors_arg: проверка входных данных на ошибки.
*/

void			check_errors_arg(int ac, char **av, t_cub *cub)
{
	if (ac != 2)
		error("ERROR: No more than 2 arguments were submitted", cub);
	else if (ft_strncmp(av[1], "map.cub", ft_strlen(av[1])))
	{
		ft_putstr_fd("ERROR: The map is not called 'map.cub' ", 1);
		error("or it is called from another folder'", cub);
	}
}

/*
** check_tab: проверка на пробелы в конце строки.
*/

void			check_tab(char *line, t_cub *cub)
{
	if (line[ft_strlen(line) - 1] == ' ')
		error("ERROR: A space was found after the indexer", cub);
}

/*
** all_tab_in_line: проверка, состоит ли строка только из пробелов.
*/

void			all_tab_in_line(char *str, t_cub *cub)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return ;
		++i;
	}
	ft_putstr_fd("ERROR: There is an empty line ", 1);
	error("with spaces at the end of the map", cub);
}

/*
** check_symbols_map_norm: функция для нормы.
*/

static	void	check_symbols_map_norm(int *flag, int *i, int *j, t_cub *cub)
{
	if (cub->p.map[*i][*j] == 'N' || cub->p.map[*i][*j] == 'S'
	|| cub->p.map[*i][*j] == 'E' || cub->p.map[*i][*j] == 'W')
	{
		if (*flag == 0)
		{
			*flag = 1;
			cub->p.playr = &cub->p.map[*i][*j];
			cub->p.playr_y = *i;
			cub->p.playr_x = *j;
		}
		else
			error("ERROR: The player meets more than 1 time", cub);
	}
}

/*
** check_symbols_map: проверка символов карты.
*/

void			check_symbols_map(int size, t_cub *cub)
{
	int i;
	int j;
	int flag;

	i = -1;
	flag = 0;
	while (++i != size)
	{
		j = 0;
		while (cub->p.map[i][j] != '\0')
		{
			check_symbols_map_norm(&flag, &i, &j, cub);
			if (cub->p.map[i][j] == ' ' || cub->p.map[i][j] == '0'
			|| cub->p.map[i][j] == '1' || cub->p.map[i][j] == '2'
			|| cub->p.map[i][j] == 'N' || cub->p.map[i][j] == 'S'
			|| cub->p.map[i][j] == 'E' || cub->p.map[i][j] == 'W')
				++j;
			else
				error("ERROR: Wrong symbol in the map", cub);
		}
	}
	if (flag == 0)
		error("ERROR: The player never meets", cub);
}
