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

#include "cub3d.h"

/*
** check_errors_arg: проверка входных данных на ошибки.
*/

void			check_errors_arg(int ac, char **av)
{
	if (ac != 2)
		error("ERROR: No more than 2 arguments were submitted");
	else if (ft_strncmp(av[1], "map.cub", ft_strlen(av[1])))
		error("ERROR: The card is not called 'map.cub'");
}

/*
** check_tab: проверка на пробелы в конце строки.
*/

void			check_tab(char *line)
{
	if (line[ft_strlen(line) - 1] == ' ')
		error("ERROR: A space was found after the indexer");
}

/*
** all_tab_in_line: проверка, состоит ли строка только из пробелов.
*/

void			all_tab_in_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return ;
		++i;
	}
	error("ERROR: There is an empty line with spaces at the end of the map");
}

/*
** check_symbols_map_norm: функция для нормы.
*/

static	void	check_symbols_map_norm(int *flag, int *i, int *j, t_parser *p)
{
	if (p->map[*i][*j] == 'N' || p->map[*i][*j] == 'S'
	|| p->map[*i][*j] == 'E' || p->map[*i][*j] == 'W')
	{
		if (*flag == 0)
		{
			*flag = 1;
			p->playr = &p->map[*i][*j];
			p->playr_y = *i;
			p->playr_x = *j;
		}
		else
			error("ERROR: The player meets more than 1 time");
	}
}

/*
** check_symbols_map: проверка символов карты.
*/

void			check_symbols_map(int size, t_parser *p)
{
	int i;
	int j;
	int flag;

	i = -1;
	flag = 0;
	while (++i != size)
	{
		j = 0;
		while (p->map[i][j] != '\0')
		{
			check_symbols_map_norm(&flag, &i, &j, p);
			if (p->map[i][j] == ' ' || p->map[i][j] == '0'
			|| p->map[i][j] == '1' || p->map[i][j] == '2'
			|| p->map[i][j] == 'N' || p->map[i][j] == 'S'
			|| p->map[i][j] == 'E' || p->map[i][j] == 'W')
				++j;
			else
				error("ERROR: Wrong symbol in the map");
		}
	}
	if (flag == 0)
		error("ERROR: The player never meets");
}
