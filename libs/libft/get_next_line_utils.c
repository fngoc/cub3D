#include "libft.h"

/*
** ft_gnlstrlen: возвращает количество символов в строке.
*/

size_t	ft_gnlstrlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		++i;
	return (i);
}

/*
** ft_gnlstrjoin:  выделяет и возвращает новую строку,
** которая является результатом конкатенации
** из 's1' и 's2'.
*/

char	*ft_gnlstrjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(p = malloc(ft_gnlstrlen(s1) + ft_gnlstrlen(s2) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		++i;
	}
	free(s1);
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		++i;
		++j;
	}
	p[i] = '\0';
	return (p);
}
