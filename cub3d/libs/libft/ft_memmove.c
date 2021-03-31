#include "libft.h"

/*
** ft_memmove: копирует n байт из массива,
** на который указывает аргумент source,
** в массив, на который указывает аргумент destination.
*/

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	const unsigned char	*s;
	const unsigned char	*last_s;
	unsigned char		*d;
	unsigned char		*last_d;

	d = destination;
	s = source;
	if (destination == NULL && source == NULL)
		return (NULL);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		last_s = s + (n - 1);
		last_d = d + (n - 1);
		while (n--)
			*last_d-- = *last_s--;
	}
	return (destination);
}
