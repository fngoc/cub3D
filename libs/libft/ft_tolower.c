#include "libft.h"

/*
** ft_tolower: выполняет преобразование прописных букв в строчные.
*/

int	ft_tolower(int c)
{
	return ((c >= 65 && c <= 90) ? (c + 32) : c);
}
