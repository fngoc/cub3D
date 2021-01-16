#include "cub3d.h"

/*
** checking_all_data: проверка на наличие всех спарсеных данных
** и что бы они встречались один раз.
*/

static	void	checking_all_data(t_parser *p)
{
	if (p->resolution_l == 0 || p->resolution_w == 0 || ft_strlen(p->north_texture) == 0
	|| ft_strlen(p->south_texture) == 0 || ft_strlen(p->west_texture) == 0
	|| ft_strlen(p->east_texture) == 0 || ft_strlen(p->sprite_texture) == 0
	|| p->floore_flag != 1 || p->ceilling_flag != 1)
	{
		ft_putendl_fd("ERROR: Was set not all edificatory or are there repetitions", 1);
		exit(1);
	}
}

/*
** checking_tab_in_R_F: проверка на пробелы в цветах.
*/

static	void	checking_tab_in_R_F(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			ft_putendl_fd("ERROR: A space was found in color", 1);
			exit(1);
		}
		++i;
	}
}

/*
** checking_tab: проверка на пробелы в конце строки.
*/

static	void	checking_tab(char *line)
{
	if (line[ft_strlen(line) - 1] == ' ')
	{
		ft_putendl_fd("ERROR: A space was found after the indexer", 1);
		exit(1);
	}
}

/*
** checking_C: проверка resolution, floore и ceilling.
*/

static	void	checking_C(t_parser *p)
{
	if ((p->ceilling_R > 255 || p->ceilling_R < 0) ||
	(p->ceilling_G > 255 || p->ceilling_G < 0) ||
	(p->ceilling_B > 255 || p->ceilling_B < 0))
	{
		ft_putendl_fd("ERROR: Not a valid ceilling color", 1);
		exit(1);
	}
	p->ceilling_flag = 1;
}

/*
** checking_F: проверка floore .
*/

static	void	checking_F(t_parser *p)
{
	if ((p->floore_R > 255 || p->floore_R < 0) ||
	(p->floore_G > 255 || p->floore_G < 0) ||
	(p->floore_B > 255 || p->floore_B < 0))
	{
		ft_putendl_fd("ERROR: Not a valid floor color", 1);
		exit(1);
	}
	p->floore_flag = 1;
}

/*
** checking_R: проверка resolution.
*/

static	void	checking_R(t_parser *p)
{
	if (p->resolution_w < 0 || p->resolution_l < 0)
	{
		ft_putendl_fd("ERROR: Not a valid resolution", 1);
		exit(1);
	}
}

/*
** get_floore: получить floore с проверкой.
*/

static	void	get_floore(char *tmp, t_parser *p)
{
	if (ft_isdigit(*tmp))
		p->floore_R = ft_atoi(tmp);
	else
	{
		ft_putendl_fd("ERROR: Not set floore_R", 1);
		exit(1);
	}
	tmp += ft_digit_num(p->floore_R) + 1;
	if (ft_isdigit(*tmp))
		p->floore_G = ft_atoi(tmp);
	else
	{
		ft_putendl_fd("ERROR: Not set floore_G", 1);
		exit(1);
	}
	tmp += ft_digit_num(p->floore_G) + 1;
	if (ft_isdigit(*tmp))
		p->floore_B = ft_atoi(tmp);
	else
	{
		ft_putendl_fd("ERROR: Not set floore_B", 1);
		exit(1);
	}
}

/*
** get_ceilling: получить ceilling с проверкой.
*/

static	void	get_ceilling(char *tmp, t_parser *p)
{
	if (ft_isdigit(*tmp))
		p->ceilling_R = ft_atoi(tmp);
	else
	{
		ft_putendl_fd("ERROR: Not set ceilling_R", 1);
		exit(1);
	}
	tmp += ft_digit_num(p->ceilling_R) + 1;
	if (ft_isdigit(*tmp))
		p->ceilling_G = ft_atoi(tmp);
	else
	{
		ft_putendl_fd("ERROR: Not set ceilling_G", 1);
		exit(1);
	}
	tmp += ft_digit_num(p->ceilling_G) + 1;
	if (ft_isdigit(*tmp))
		p->ceilling_B = ft_atoi(tmp);
	else
	{
		ft_putendl_fd("ERROR: Not set ceilling_B", 1);
		exit(1);
	}
}

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
		checking_tab_in_R_F(tmp);
		get_floore(tmp, p);
		checking_F(p);
	}
	else if (id == 8)
	{
		checking_tab_in_R_F(tmp);
		get_ceilling(tmp, p);
		checking_C(p);
	}
}

/*
** parser_inf: парсинг информации в зависимости от индификаторов.
*/

static	void	parser_inf(char *line, int id, int index, t_parser *p)
{
	char *tmp;

	while (line[index]  == ' ' || line[index]  == '\t')
		++index;
	tmp = &line[index];
	if (id == 1)
	{
		p->resolution_w = ft_atoi(tmp);
		tmp += ft_digit_num(p->resolution_w);
		p->resolution_l = ft_atoi(tmp);
		checking_R(p);
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
	while (line[index]  == ' ' || line[index]  == '\t')
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
	{
		ft_putendl_fd("ERROR: File not found or not open", 1);
		exit(1);
	}
	while (get_next_line(fd, &line) && coll_line++ != 8)
	{
		if (ft_strlen(line) == 0)
			coll_line--;
		else
		{
			checking_tab(line);
			parser_data(line, p);
			if (coll_line == 8)
			{
				checking_all_data(p);
				parser_map(fd, p);
			}
		}
	}

	/* Печать даннх */
	printf("R: %d|\nR: %d|\nNO: %s|\nSO: %s|\nWE: %s|\nEA: %s|\nS: %s|\nfloore_R: %d|\nfloore_G: %d|\nfloore_B: %d|\nceilling_R: %d|\nceilling_G: %d|\nceilling_B: %d|\n", p->resolution_w, p->resolution_l, p->north_texture, p->south_texture, p->west_texture, p->east_texture, p->sprite_texture, p->floore_R, p->floore_G, p->floore_B, p->ceilling_R, p->ceilling_G, p->ceilling_B);
	
	/* Печать индекса игрока */
	printf("Player is here: %c\n", *p->playr);

	/* Печать карты */
	int i = -1;
	while (p->map[++i])
		ft_putendl_fd(p->map[i], 1);
}
