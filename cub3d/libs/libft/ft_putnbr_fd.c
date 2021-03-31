#include "libft.h"

/*
** ft_putnbr_fd: Выводит целое число 'n'
** в указанный файл дескриптор.
*/

static void	print_symbole(long int n, int fd)
{
	if (n > 9)
		print_symbole(n / 10, fd);
	ft_putchar_fd((n % 10 + '0'), fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		print_symbole((long int)n * (-1), fd);
	}
	else
		print_symbole((long int)n, fd);
}
