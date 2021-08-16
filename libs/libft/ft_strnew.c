#include "libft.h"

/*
** ft_strnew: создает новую строку размером size
** и заполняет ее нулями.
*/

char	*ft_strnew(unsigned int size)
{
	char	*str;

	if (!(str = malloc(sizeof(char) * size + 1)))
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}
