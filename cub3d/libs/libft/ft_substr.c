/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:43:44 by fngoc             #+#    #+#             */
/*   Updated: 2020/10/30 16:43:51 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_substr: выделяет и возвращает подстроку
** из строки 's'. Подстрока начинается с
** индекса ’start’ и имеет максимальный размер 'len'.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	int		i;
	int		j;

	p = malloc(len + 1);
	i = start;
	j = 0;
	if (p == NULL || s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p[0] = '\0';
		return (p);
	}
	while (len-- != 0 && s[i] != '\0')
	{
		p[j] = s[i];
		++j;
		++i;
	}
	p[j] = '\0';
	return (p);
}
