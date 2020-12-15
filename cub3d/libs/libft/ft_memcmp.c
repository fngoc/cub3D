/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:25:26 by fngoc             #+#    #+#             */
/*   Updated: 2020/10/30 11:25:39 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memcmp: сравнивает первые n символов
** массивов, адресуемых параметрами s1 и s2.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *tmp1;
	const unsigned char *tmp2;

	tmp1 = s1;
	tmp2 = s2;
	while (n != 0)
	{
		if (*tmp1 == *tmp2)
		{
			tmp1++;
			tmp2++;
			n--;
		}
		else
			return (*tmp1 - *tmp2);
	}
	return (0);
}
