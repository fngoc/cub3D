#include "libft.h"

/*
** ft_atoi: конвертирует строку, на которую
** указывает параметр str, в величину типа int.
*/

int	ft_atoi(const char *str)
{
	int			i;
	long int	n;
	int			sign;

	i = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		++i;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		n = 10 * n + (str[i] - '0');
		if ((n > 2147483647 && sign == 1) ||
			(n < -2147483647 && sign == -1))
			return ((sign == 1) ? -1 : 0);
		i++;
	}
	return (sign * n);
}
