#include "libft.h"

/*
** ft_putchar_fd: Выводит символ 'c'
** в указанный файл дескриптор.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
