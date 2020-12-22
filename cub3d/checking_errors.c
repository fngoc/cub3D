#include "cub3d.h"

/*
** checking_errors: проверка входных данных на ошибки. 
*/

void checking_errors(int ac, char **av)
{
    (void)av;
    if (ac != 2)
    {
        ft_putstr_fd("ERROR: No more than 2 arguments were submitted\n", 1);
        exit(1);
    }
}
