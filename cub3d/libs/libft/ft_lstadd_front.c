/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:52:44 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/01 23:57:05 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_lstadd_front: Добавляет элемент "new"
** в начало списока.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
