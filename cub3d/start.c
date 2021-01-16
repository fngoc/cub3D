#include "cub3d.h"

/*
** start: запуск окна.
*/

void start(void *mlx, void *mlx_win, t_parser *p)
{
	int x;
	int y;

	x = 100;
	y = 100;
    mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, p->resolution_w, p->resolution_l, "cub3d");
	while (y++ < 200)
	{
		x = 100;
		while (x++ < 200)
			mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);
	}
	mlx_loop(mlx);
}
