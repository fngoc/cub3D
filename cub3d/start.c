#include "cub3d.h"

/*
** start: запуск.
*/

void start(void *mlx, void *win, t_parser *p)
{
    mlx = mlx_init();
	win = mlx_new_window(mlx, p->resolution_w, p->resolution_l, "test");
	mlx_loop(mlx);
}