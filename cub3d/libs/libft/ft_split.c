/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:42:46 by fngoc             #+#    #+#             */
/*   Updated: 2020/10/31 15:42:48 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_split: Выделяет и возвращает массив строк,
** полученных путем разделения 's' с помощью
** символ ’c’ в качестве разделителя.
** Массив должен быть заканчивается указателем NULL.
*/

static int	ft_word_count(char const *s, char c)
{
	int	state;
	int	word_count;

	state = 0;
	word_count = 0;
	while (*s)
	{
		if (*s == c)
		{
			state = 0;
			s++;
		}
		else if (state == 0)
		{
			state = 1;
			word_count++;
			s++;
		}
		else
			s++;
	}
	return (word_count);
}

static char	*ft_alloc_word(char const *s, char c)
{
	int		size;
	char	*p;

	size = 0;
	p = 0;
	while ((s[size]) && (s[size] != c))
		size++;
	if (!(p = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_strlcpy(p, s, size + 1);
	return (p);
}

char		**ft_split(char const *s, char c)
{
	int		count;
	int		words;
	char	**map;

	count = -1;
	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	if (!(map = malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (++count < words)
	{
		while (s[0] == c)
			s++;
		if (!(map[count] = ft_alloc_word(s, c)))
		{
			while (count > 0)
				free(map[count--]);
			free(map);
			return (NULL);
		}
		s += ft_strlen(map[count]);
	}
	map[count] = NULL;
	return (map);
}
