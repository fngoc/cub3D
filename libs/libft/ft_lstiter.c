#include "libft.h"

/*
** ft_lstiter: Итерируем список ’lst’ и применяем
** функцию'f' к содержанию каждого элемента.
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *p;

	while (lst)
	{
		p = lst->next;
		f(lst->content);
		lst = p;
	}
}
