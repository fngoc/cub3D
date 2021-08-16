#include "libft.h"

/*
** ft_lstnew: Выделяет и возвращает новый элемент.
** Инициализируется содержимое переменной со
** значением параметра 'content'. В переменную
** ’next’ инициализируется значением NULL.
*/

t_list	*ft_lstnew(void *content)
{
	t_list *list;

	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
