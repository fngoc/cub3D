#include "libft.h"

/*
** ft_toupper: возвращает соответствующий верхнему
** регистру эквивалент символа c, если c — это буква.
*/

int	ft_toupper(int c)
{
	return ((c >= 97 && c <= 122) ? (c - 32) : c);
}
