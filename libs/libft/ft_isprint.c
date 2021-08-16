#include "libft.h"

/*
** ft_isprint: возвращает ненулевое значение
** если c это печатаемый символ (0x20 - 0x7E).
*/

int	ft_isprint(int c)
{
	return ((c >= 32) && (c <= 126));
}
