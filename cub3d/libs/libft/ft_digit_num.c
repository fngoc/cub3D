#include "libft.h"

/*
** ft_digit_num: подсчет количества цифр в числе.
*/

int		ft_digit_num(long int n)
{
	int tmp;
	int tmp2;

	tmp2 = (int)n;
	tmp = 1;
	if (n < 0)
		++tmp;
	while ((tmp2 = tmp2 / 10))
		++tmp;
	return (tmp);
}