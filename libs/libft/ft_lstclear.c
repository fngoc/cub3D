#include "libft.h"

/*
** ft_lstclear: удаляет и освобождает данный элемент и
** каждый преемник этого элемента, используя функцию 'del'
** Наконец, указатель на список должен быть установлен на NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *p;

	while (*lst)
	{
		p = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = p;
	}
	*lst = NULL;
}
