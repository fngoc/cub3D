#include "libft.h"

/*
** ft_strlcpy: копирует из строки src в
** буфер dst не более чем size - 1 символов
** и гарантированно устанавливает в
** конец строки нулевой символ.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;

	n = size;
	d = dst;
	s = src;
	if (dst == NULL || src == NULL)
		return (0);
	if (n != 0)
	{
		while (--n != 0)
		{
			if ((*d++ = *s++) == '\0')
				break ;
		}
	}
	if (n == 0)
	{
		if (size != 0)
			*d = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
