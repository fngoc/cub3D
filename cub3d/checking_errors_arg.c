#include "cub3d.h"

/*
** checking_errors_arg: проверка входных данных на ошибки. 
*/

void    checking_errors_arg(int ac, char **av)
{
    (void)av;
    if (ac != 2)
    {
        ft_putstr_fd("ERROR: No more than 2 arguments were submitted\n", 1);
        exit(1);
    }
    else if (ft_strncmp(av[1], "map.cub", ft_strlen(av[1])))
    {
        ft_putstr_fd("ERROR: The card is not called 'map.cub'\n", 1);
        exit(1);
    }
}
