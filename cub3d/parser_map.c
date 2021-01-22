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

static	void	check_zero(int size, t_cub *cub)
{
	int i;
	int j;

	i = -1;
	while (++i != size)
	{
		j = 0;
		while (cub->p.map[i][j] != '\0')
		{
			if ((i == 0 && cub->p.map[i][j] == '0')
			|| (i == size - 1 && cub->p.map[i][j] == '0'))
				error("ERROR: There is an empty space next to zero");
			else if (cub->p.map[i][j] == '0')
			{
				if (cub->p.map[i][j + 1] == ' ' || cub->p.map[i][j + 1] == '\0'
				|| cub->p.map[i][j - 1] == ' ' || cub->p.map[i][j - 1] == '\0'
				|| cub->p.map[i + 1][j] == ' ' || cub->p.map[i + 1][j] == '\0'
				|| cub->p.map[i - 1][j] == ' ' || cub->p.map[i - 1][j] == '\0')
					error("ERROR: There is an empty space next to zero");
			}
			++j;
		}
	}
}

/*
** set_dir: установка направления движения игрока.
*/

static	void	set_dir(int x, int y, t_cub *cub)
{
	if (cub->p.map[y][x] == 'N')
		cub->plr.dir = PI / 2;
	if (cub->p.map[y][x] == 'W')
		cub->plr.dir = PI;
	if (cub->p.map[y][x] == 'E')
		cub->plr.dir = 2 * PI;
	if (cub->p.map[y][x] == 'S')
		cub->plr.dir = (3 * PI) / 2;
}

/*
** check_cset_dirlosed_map: проверка на закрытость стенами персонажа
** с помощью алгоритма flood fill.
*/

static	void	check_closed_map(int x, int y, t_cub *cub, int size_map)
{
	if (x < 0 || y < 0 || y >= size_map || x >= (int)ft_strlen(cub->p.map[y]))
		error("ERROR: The player is not surrounded by walls");
	if (ft_strchr(" 02NWES", cub->p.map[y][x]))
	{
		if (cub->p.map[y][x] == 'N' || cub->p.map[y][x] == 'W'
		|| cub->p.map[y][x] == 'E' || cub->p.map[y][x] == 'S')
			set_dir(x, y, cub);
		if (cub->p.map[y][x] == '2')
			cub->p.map[y][x] = 'B';
		else
			cub->p.map[y][x] = '*';
		check_closed_map(x + 1, y, cub, size_map);
		check_closed_map(x - 1, y, cub, size_map);
		check_closed_map(x, y + 1, cub, size_map);
		check_closed_map(x, y - 1, cub, size_map);
	}
}

/*
** make_map: создание карты.
*/

static	void	make_map(t_list **head, int size, t_cub *cub)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = *head;
	cub->p.map = ft_calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		cub->p.map[++i] = tmp->content;
		tmp = tmp->next;
	}
	all_tab_in_line(cub->p.map[size - 1]);
	check_symbols_map(size, cub);
	check_zero(size, cub);
	check_closed_map(cub->p.playr_x, cub->p.playr_y, cub, size);
	cub->p.size_map = size;
}

/*
** parser_map: парсинг карты.
*/

void			parser_map(int fd, t_cub *cub)
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
	make_map(&head, ft_lstsize(head), cub);
}
