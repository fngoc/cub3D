#include "cub3d.h"

/*
** floodFill: проверка на закрытость стенами персонажа.
*/

static void floodFill(int x, int y, int oldcolor, int newcolor, t_parser *p)
{
	printf("%d\n", x);
	printf("%d\n", y);
	if(x >= 0 && y >= 0)
	{
		printf("%c<<<<<<\n", p->map[x][y]);
		floodFill(x + 1, y, oldcolor, newcolor, p);
		floodFill(x, y + 1, oldcolor, newcolor, p);
		floodFill(x - 1, y, oldcolor, newcolor, p);
		floodFill(x, y - 1, oldcolor, newcolor, p);
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
					p->playr_x = i;
					p->playr_y = j;
				}
				else
				{
					ft_putendl_fd("ERROR: The player meets more than 1 time", 1);
					exit(1);
				}
			}
			if (p->map[i][j] == ' ' || p->map[i][j] == '0'
			|| p->map[i][j] == '1' || p->map[i][j] == '2'
			|| p->map[i][j] == 'N' || p->map[i][j] == 'S'
			|| p->map[i][j] == 'E' || p->map[i][j] == 'W')
				++j;
			else
			{
				ft_putendl_fd("ERROR: Wrong symbol in the map", 1);
				exit(1);
			}
		}
		++i;
	}
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
	{
		ft_putendl_fd("ERROR: There is an empty line with spaces at the end of the map", 1);
		exit(1);
	}
	check_symbols_map(size, p);
	floodFill(p->playr_x, p->playr_y, '0', 'X', p);
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
