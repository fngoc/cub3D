#include "libft.h"

/*
** bzero: записывает n обнуленных байтов в строку s.
** Если n равно ноль, bzero ничего не делает.
*/

void	ft_bzero(void *s, size_t n)
{
	char *tmp;

	if (n == 0)
		return ;
	tmp = s;
	while (n-- != 0)
		*tmp++ = '\0';
}
