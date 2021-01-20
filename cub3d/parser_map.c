/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:20:16 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/18 14:27:57 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check_zero: проверка на отсутствие пустоты рядом с 0 в карте.
*/

static	void	check_zero(int size, t_parser *p)
{
	int i;
	int j;

	i = -1;
	while (++i != size)
	{
		j = 0;
		while (p->map[i][j] != '\0')
		{
			if ((i == 0 && p->map[i][j] == '0')
			|| (i == size - 1 && p->map[i][j] == '0'))
				error("ERROR: There is an empty space next to zero");
			else if (p->map[i][j] == '0')
			{
				if (p->map[i][j + 1] == ' ' || p->map[i][j + 1] == '\0'
				|| p->map[i][j - 1] == ' ' || p->map[i][j - 1] == '\0'
				|| p->map[i + 1][j] == ' ' || p->map[i + 1][j] == '\0'
				|| p->map[i - 1][j] == ' ' || p->map[i - 1][j] == '\0')
					error("ERROR: There is an empty space next to zero");
			}
			++j;
		}
	}
}

/*
** check_closed_map: проверка на закрытость стенами персонажа
** с помощью алгоритма flood fill.
*/

static	void	check_closed_map(int x, int y, t_parser *p, int size_map)
{
	if (x < 0 || y < 0 || y >= size_map || x >= (int)ft_strlen(p->map[y]))
		error("ERROR: The player is not surrounded by walls");
	if (ft_strchr(" 02NWES", p->map[y][x]))
	{
		if (p->map[y][x] == '2')
			p->map[y][x] = 'B';
		else
			p->map[y][x] = '*';
		check_closed_map(x + 1, y, p, size_map);
		check_closed_map(x - 1, y, p, size_map);
		check_closed_map(x, y + 1, p, size_map);
		check_closed_map(x, y - 1, p, size_map);
	}
}

/*
** make_map: создание карты.
*/

static	void	make_map(t_list **head, int size, t_parser *p)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = *head;
	p->map = ft_calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		p->map[++i] = tmp->content;
		tmp = tmp->next;
	}
	all_tab_in_line(p->map[size - 1]);
	check_symbols_map(size, p);
	check_zero(size, p);
	check_closed_map(p->playr_x, p->playr_y, p, size);
	p->size_map = size;
}

/*
** parser_map: парсинг карты.
*/

void			parser_map(int fd, t_parser *p)
{
	char	*line;
	t_list	*head;

	head = NULL;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) == 0)
			continue ;
		else
			ft_lstadd_back(&head, ft_lstnew(line));
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	make_map(&head, ft_lstsize(head), p);
}
