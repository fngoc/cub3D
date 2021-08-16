#include "libft.h"

/*
** ft_calloc: выделяет блок памяти для массива
** размером — count элементов, каждый из
** которых занимает size байт, и инициализирует
** все свои биты нулями.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
