#include "cub3d.h"

/*
** checking_zero: проверка на отсутствие пустоты рядом с 0 в карте.
*/

static	void	checking_zero(int size, t_parser *p)
{
	int i;
	int j;

	i = 0;
	while (i != size)
	{
		j = 0;
		while (p->map[i][j] != '\0')
		{
			if ((i == 0 && p->map[i][j] == '0') || (i == size - 1 && p->map[i][j] == '0'))
				error("ERROR: There is an empty space next to zero");
			else if (p->map[i][j] == '0')
			{
				if (p->map[i][j + 1] == ' ' || p->map[i][j + 1] == '\0')
					error("ERROR: There is an empty space next to zero");
				if (p->map[i][j - 1] == ' ' || p->map[i][j - 1] == '\0')
					error("ERROR: There is an empty space next to zero");
				if (p->map[i + 1][j] == ' ' || p->map[i + 1][j] == '\0')
					error("ERROR: There is an empty space next to zero");
				if (p->map[i - 1][j] == ' ' || p->map[i - 1][j] == '\0')
					error("ERROR: There is an empty space next to zero");
			}
			++j;
		}
		++i;
	}
}

/*
** check_closed_map: проверка на закрытость стенами персонажа
** с помощью алгоритма flood fill.
*/

static	void	check_closed_map(int x, int y, t_parser *p)
{
	// printf("-----\ny: %d\nx: %d\n-----\n", y, x);
	if (x < 0 || y < 0 || y >= (int)ft_strlen(*p->map) || x >= (int)ft_strlen(p->map[y])
		|| p->map[y][x] == ' ')
		error("ERROR: The player is not surrounded by walls");
	if (ft_strchr(" 02NWES", p->map[y][x]))
	{
		if (p->map[y][x] == '2')
			p->map[y][x] = 'B';
		else
			p->map[y][x] = '*';
		check_closed_map(x + 1, y, p);
		check_closed_map(x - 1, y, p);
		check_closed_map(x, y + 1, p);
		check_closed_map(x, y - 1, p);
	}
}

/*
** check_symbols_map: проверка символов карты.
*/

static	void	check_symbols_map(int size, t_parser *p)
{
	int i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	while (i != size)
	{
		j = 0;
		while (p->map[i][j] != '\0')
		{
			if (p->map[i][j] == 'N' || p->map[i][j] == 'S'
			|| p->map[i][j] == 'E' || p->map[i][j] == 'W')
			{
				if (flag == 0)
				{
					flag = 1;
					p->playr = &p->map[i][j];
					p->playr_y = i;
					p->playr_x = j;
				}
				else
					error("ERROR: The player meets more than 1 time");
			}
			if (p->map[i][j] == ' ' || p->map[i][j] == '0'
			|| p->map[i][j] == '1' || p->map[i][j] == '2'
			|| p->map[i][j] == 'N' || p->map[i][j] == 'S'
			|| p->map[i][j] == 'E' || p->map[i][j] == 'W')
				++j;
			else
				error("ERROR: Wrong symbol in the map");
		}
		++i;
	}
	if (flag == 0)
		error("ERROR: The player never meets");
}

/*
** all_tab_in_line: проверка, состоит ли строка только из пробелов.
*/

static int all_tab_in_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		++i;
	}
	return (1);
}

/*
** make_map: создание карты.
*/

static void make_map(t_list **head, int size, t_parser *p)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = *head;
	p->map = ft_calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		p->map[++i] = tmp->content;
		tmp= tmp->next;
	}
	if (all_tab_in_line(p->map[size - 1]))
		error("ERROR: There is an empty line with spaces at the end of the map");
	check_symbols_map(size, p);
	checking_zero(size, p);
	check_closed_map(p->playr_x, p->playr_y, p);
}

/*
** parser_map: парсинг карты.
*/

void parser_map(int fd, t_parser *p)
{
	char	*line;
	t_list	*head;

	line = NULL;
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
