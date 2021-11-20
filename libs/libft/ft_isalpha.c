#include "libft.h"

/*
** ft_isalpha: возвращает ненулевое значение,
** если ее аргумент 'c' является буквой, в противном
** случае возвращается нуль.
*/

int	ft_isalpha(int c)
{
	return (((c >= 65) && (c <= 90)) ||
			((c >= 97) && (c <= 122)) ? 1 : 0);
}