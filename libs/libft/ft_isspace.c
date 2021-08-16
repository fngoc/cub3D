#include "libft.h"

/*
** ft_isspace: проверяет символ на символы табуляции.
*/

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
	c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
