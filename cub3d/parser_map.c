#include "cub3d.h"

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