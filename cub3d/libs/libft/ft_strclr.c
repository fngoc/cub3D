#include "libft.h"

/*
** ft_strclr: очищает строку.
*/

void	ft_strclr(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}
