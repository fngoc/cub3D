/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:18:01 by fngoc             #+#    #+#             */
/*   Updated: 2020/10/30 11:18:12 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memccpy: копирует данные из массива, на который
** указывает аргумент src, в массив, на который указывает
** аргумент dst пока не встретится символ c, или пока не
** будет скопировано n байт данных.
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (n-- != 0)
	{
		if (((unsigned char *)src)[i] != (unsigned char)c)
		{
			*((unsigned char *)dst) = ((unsigned char *)src)[i++];
			++dst;
		}
		else
		{
			*((unsigned char *)dst) = ((unsigned char *)src)[i];
			++dst;
			return (dst);
		}
	}
	return (NULL);
}
