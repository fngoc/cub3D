/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:25:06 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/02 00:00:05 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strdup: дублирует строку, на
** которую указывает аргумент str.
*/

char	*ft_strdup(const char *s1)
{
	char	*str_dup;
	char	*p;

	str_dup = malloc(ft_strlen(s1) + 1);
	p = str_dup;
	if (str_dup == NULL)
		return (NULL);
	while (*s1)
		*p++ = *s1++;
	*p = '\0';
	return (str_dup);
}
