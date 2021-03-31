#include "libft.h"

/*
** ft_lstlast: Возвращает последний элемент списка.
*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list *p;
	t_list *l;

	p = lst;
	l = p;
	while (p != NULL)
	{
		l = p;
		p = p->next;
	}
	return (l);
}
