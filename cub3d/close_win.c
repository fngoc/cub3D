#include "cub3d.h"

/*
** close_win: закрытие окна и выход из программы.
*/

int close_win(t_cub *cub)
{
    mlx_destroy_window(cub->mlx, cub->mlx_win);
    // free(cub);
    exit(0);
    return (0);
}
