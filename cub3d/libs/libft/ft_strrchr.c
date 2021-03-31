#include "libft.h"

/*
** ft_strrchr: возвращает указатель на последнее
** вхождение младшего байта аргумента c в строке,
** на которую указывает str.
*/

char	*ft_strrchr(const char *s, int c)
{
	const char	*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			tmp = &s[i];
		++i;
	}
	if (c == '\0')
		return (&((char *)s)[i]);
	if (tmp != NULL)
		return ((char *)tmp);
	return (NULL);
}
