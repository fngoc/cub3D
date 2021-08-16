#include "libft.h"

/*
** ft_memset: заполняет первые len байтов значением c
** (преобразованных в unsigned char) в строке b.
*/

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;

	tmp = b;
	while (len-- != 0)
		*tmp++ = c;
	return (b);
}
