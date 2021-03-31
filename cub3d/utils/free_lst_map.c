#include "../cub3d.h"

/*
** free_lst_map: очистить лист с картой.
*/

void	free_lst_map(t_list **lst)
{
	t_list *p;

	while (*lst)
	{
		p = (*lst)->next;
		free(*lst);
		*lst = p;
	}
	*lst = NULL;
}
