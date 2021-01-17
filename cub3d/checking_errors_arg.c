#include "cub3d.h"

/*
** checking_errors_arg: проверка входных данных на ошибки. 
*/

void    checking_errors_arg(int ac, char **av)
{
    if (ac != 2)
        error("ERROR: No more than 2 arguments were submitted");
    else if (ft_strncmp(av[1], "map.cub", ft_strlen(av[1])))
        error("ERROR: The card is not called 'map.cub'");
}
