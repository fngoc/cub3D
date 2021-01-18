/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:20:23 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/18 14:19:50 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** parser_inf_norm: функция для нормы.
*/

static	void	parser_inf_norm(char *line, int id, int index, t_parser *p)
{
	char *tmp;

	tmp = &line[index];
	if (id == 6)
		p->sprite_texture = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 7)
	{
		check_tab_in_r_f(tmp);
		get_floore(tmp, p);
		check_f(p);
	}
	else if (id == 8)
	{
		check_tab_in_r_f(tmp);
		get_ceilling(tmp, p);
		check_c(p);
	}
}

/*
** parser_inf: парсинг информации в зависимости от индификаторов.
*/

static	void	parser_inf(char *line, int id, int index, t_parser *p)
{
	char *tmp;

	while (line[index] == ' ' || line[index] == '\t')
		++index;
	tmp = &line[index];
	if (id == 1)
	{
		p->resolution_w = ft_atoi(tmp);
		tmp += ft_digit_num(p->resolution_w);
		p->resolution_l = ft_atoi(tmp);
		check_r(p);
	}
	else if (id == 2)
		p->north_texture = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 3)
		p->south_texture = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 4)
		p->west_texture = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 5)
		p->east_texture = ft_substr(line, index, ft_strlen(tmp));
	else
		parser_inf_norm(line, id, index, p);
}

/*
** parser_data: парсинг данных.
*/

static	void	parser_data(char *line, t_parser *p)
{
	int index;

	index = 0;
	while (line[index] == ' ' || line[index] == '\t')
		++index;
	if (line[index] == 'R')
		parser_inf(line, 1, ++index, p);
	else if (line[index] == 'F')
		parser_inf(line, 7, ++index, p);
	else if (line[index] == 'C')
		parser_inf(line, 8, ++index, p);
	else if (line[index++] == 'N' && line[index] == 'O')
		parser_inf(line, 2, ++index, p);
	else if (line[--index] == 'S' && line[++index] == 'O')
		parser_inf(line, 3, ++index, p);
	else if (line[index] == 'W' && line[++index] == 'E')
		parser_inf(line, 4, ++index, p);
	else if (line[index] == 'E' && line[++index] == 'A')
		parser_inf(line, 5, ++index, p);
	else if (line[--index] == 'S' && !ft_isalpha(line[++index]))
		parser_inf(line, 6, index, p);
}

/*
** parse: парсинг данных и  карты.
*/

void			parser(char **argv, t_parser *p)
{
	int		fd;
	int		coll_line;
	char	*line;

	coll_line = 0;
	if (!(fd = open(argv[1], O_RDONLY)))
		error("ERROR: File not found or not open");
	while (get_next_line(fd, &line) && coll_line++ != 8)
	{
		if (ft_strlen(line) == 0)
			coll_line--;
		else
		{
			check_tab(line);
			parser_data(line, p);
			if (coll_line == 8)
			{
				check_all_data(p);
				parser_map(fd, p);
			}
		}
	}
}
