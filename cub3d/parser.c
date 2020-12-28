#include "cub3d.h"

/*
** parser_inf_norm: функция для нормы.
*/

static void	parser_inf_norm(char *line, int id, int index, t_parser *p)
{
	char *tmp;

	tmp = &line[index];
	if (id == 6)
		p->sprite_texture = ft_substr(line, index, ft_strlen(tmp));
	else if (id == 7)
	{
		p->floore_R = ft_atoi(tmp);
		tmp += ft_digit_num(p->floore_R) + 1;
		p->floore_G = ft_atoi(tmp);
		tmp += ft_digit_num(p->floore_G) + 1;
		p->floore_B = ft_atoi(tmp);
	}
	else if (id == 8)
	{
		p->ceilling_R = ft_atoi(tmp);
		tmp += ft_digit_num(p->ceilling_R) + 1;
		p->ceilling_G = ft_atoi(tmp);
		tmp += ft_digit_num(p->ceilling_G) + 1;
		p->ceilling_B = ft_atoi(tmp);
	}
}

/*
** parser_inf: парсинг информации в зависимости от индификаторов.
*/

static void	parser_inf(char *line, int id, int index, t_parser *p)
{
	char *tmp;

	while (line[index] == ' ')
		++index;
	tmp = &line[index];
	if (id == 1)
	{
		p->resolution_w = ft_atoi(tmp);
		tmp += ft_digit_num(p->resolution_w);
		p->resolution_l = ft_atoi(tmp);
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

static void	parser_data(char *line, t_parser *p)
{
	int index;

	index = 0;
	while (line[index] == ' ')
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
** make_map: создание карты.
*/

void make_map(t_list *lst_map, int size)
{
	char	**map;
	int 	i;
	t_list	*tmp;

	i = -1;
	tmp = lst_map;
	map = ft_calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	/* Вывод карты */
	i = -1;
	while (map[++i])
		printf("%s\n", map[i]);
}

/*
** parser_map: парсинг карты.
*/

void parser_map(int fd , t_list *lst_map)
{
	char	*line;

	while (get_next_line(fd, &line))
		ft_lstadd_back(&lst_map, ft_lstnew(line));
	ft_lstadd_back(&lst_map, ft_lstnew(line));
	make_map(lst_map, ft_lstsize(lst_map));
}

/*
** parse: парсинг данных и  карты.
*/

void		parser(char **argv, t_parser *p, t_list	*lst_map)
{
	int		fd;
	int		coll;
	char	*line;

	coll = 0;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) && coll++ != 8)
	{
		if (ft_strlen(line) == 0)
			coll--;
		else
			parser_data(line, p);
	}
	parser_map(fd ,lst_map);
	//printf("R: %d\nR: %d\nNO: %s\nSO: %s\nWE: %s\nEA: %s\nS: %s\nfloore_R: %d\nfloore_G: %d\nfloore_B: %d\nceilling_R: %d\nceilling_G: %d\nceilling_B: %d\n", p->resolution_w, p->resolution_l, p->north_texture, p->south_texture, p->west_texture, p->east_texture, p->sprite_texture, p->floore_R, p->floore_G, p->floore_B, p->ceilling_R, p->ceilling_G, p->ceilling_B);
}