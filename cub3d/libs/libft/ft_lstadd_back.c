#include "libft.h"

/*
** ft_lstadd_back: добавляет новый элемент в конец списка.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *p;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	if ((p = ft_lstlast(*lst)) != NULL)
		p->next = new;
}
