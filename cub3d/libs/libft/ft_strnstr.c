/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:55:30 by fngoc             #+#    #+#             */
/*   Updated: 2020/10/30 11:55:39 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strnstr: ищет первое вхождение строки (за исключением
** признак конца строки), на которую указывает
** аргумент haystack, в строку, на которую указывает
** аргумент needle. Если строка haystack имеет
** нулевую длину, то функция вернет указатель
** на начало строки needle.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		*segfault;
	size_t	needle_len;

	i = 0;
	segfault = 0;
	if (haystack == NULL || needle == NULL)
		*segfault = 1;
	if ((needle_len = ft_strlen(needle)) == 0)
		return ((char *)haystack);
	while (i++ <= (int)(len - needle_len))
	{
		if ((haystack[0] == needle[0]) &&
			(ft_strncmp(haystack, needle, needle_len)) == 0)
			return ((char *)haystack);
		++haystack;
	}
	return (NULL);
}
