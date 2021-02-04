/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:20:23 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/04 22:29:47 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** parser_inf_norm: функция для нормы.
*/

static	void	parser_inf_norm(char *line, int id, int index, t_cub *cub)
{
	char *tmp;

	tmp = &line[index];
	if (id == 6)
		cub->p.spr_tex = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 7)
	{
		check_tab_in_r_f(tmp, cub);
		get_floore(tmp, cub);
		check_f(cub);
	}
	else if (id == 8)
	{
		check_tab_in_r_f(tmp, cub);
		get_ceilling(tmp, cub);
		check_c(cub);
	}
}

/*
** parser_inf: парсинг информации в зависимости от индификаторов.
*/

static	void	parser_inf(char *line, int id, int index, t_cub *cub)
{
	char *tmp;

	while (line[index] == ' ' || line[index] == '\t')
		++index;
	tmp = &line[index];
	if (id == 1)
	{
		cub->p.res_w = ft_atoi(tmp);
		tmp += ft_digit_num(cub->p.res_w);
		cub->p.res_l = ft_atoi(tmp);
		check_r(cub);
	}
	else if (id == 2)
		cub->p.nor_tex = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 3)
		cub->p.sou_tex = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 4)
		cub->p.wes_tex = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 5)
		cub->p.eas_tex = ft_substr(line, index, ft_strlen(tmp));
	else
		parser_inf_norm(line, id, index, cub);
}

/*
** parser_data: парсинг данных.
*/

static	void	parser_data(char *line, t_cub *cub)
{
	int index;

	index = 0;
	while (line[index] == ' ' || line[index] == '\t')
		++index;
	if (line[index] == 'R')
		parser_inf(line, 1, ++index, cub);
	else if (line[index] == 'F')
		parser_inf(line, 7, ++index, cub);
	else if (line[index] == 'C')
		parser_inf(line, 8, ++index, cub);
	else if (line[index++] == 'N' && line[index] == 'O')
		parser_inf(line, 2, ++index, cub);
	else if (line[--index] == 'S' && line[++index] == 'O')
		parser_inf(line, 3, ++index, cub);
	else if (line[index] == 'W' && line[++index] == 'E')
		parser_inf(line, 4, ++index, cub);
	else if (line[index] == 'E' && line[++index] == 'A')
		parser_inf(line, 5, ++index, cub);
	else if (line[--index] == 'S' && !ft_isalpha(line[++index]))
		parser_inf(line, 6, index, cub);
}

/*
** parse: парсинг данных и  карты.
*/

void			parser(char **argv, t_cub *cub)
{
	int		fd;
	int		coll_line;
	char	*line;

	coll_line = 0;
	if (!(fd = open(argv[1], O_RDONLY)))
		error("ERROR\nFile not found or not open", cub);
	while (get_next_line(fd, &line) && coll_line++ != 8)
	{
		if (ft_strlen(line) == 0)
			coll_line--;
		else
		{
			check_tab(line, cub);
			parser_data(line, cub);
			if (coll_line == 8)
			{
				check_all_data(cub);
				parser_map(fd, cub);
			}
		}
		free(line);
	}
	free(line);
}
