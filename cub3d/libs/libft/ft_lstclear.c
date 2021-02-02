/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:49:30 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/01 23:57:08 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
