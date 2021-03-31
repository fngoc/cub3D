#include "../cub3d.h"

/*
** error: печатает текст ошибки и выходит из программы.
*/

void	error(char *str, t_cub *cub)
{
	(void)cub;
	ft_putendl_fd(str, 1);
	exit(1);
}
