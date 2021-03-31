#include "libft.h"

/*
** ft_strtrim: возвращает строку с удаленными
** символами 'set' по бокам.
*/

static int	is_char(char const c, char const *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		++i;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int start;
	int end;

	start = 0;
	if (s1 == NULL)
		return (NULL);
	end = (int)ft_strlen(s1) - 1;
	while (is_char(s1[end], set))
		if (end > 0)
			--end;
		else
			break ;
	++end;
	while (is_char(s1[start], set))
		++start;
	if (start == (int)ft_strlen(s1))
		return (ft_substr("", 0, 1));
	return (ft_substr(s1, start, end - start));
}
