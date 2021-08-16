#include "../cub3d.h"

/*
** turn_left: повернуть влево.
*/

void	turn_left(t_cub *cub, double r)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = cub->plr.dir_y;
	old_plane_x = cub->plr.plane_y;
	cub->plr.dir_y = cub->plr.dir_y * cos(r) - cub->plr.dir_x * sin(r);
	cub->plr.dir_x = old_dir_x * sin(r) + cub->plr.dir_x * cos(r);
	cub->plr.plane_y = cub->plr.plane_y * cos(r) - cub->plr.plane_x * sin(r);
	cub->plr.plane_x = old_plane_x * sin(r) + cub->plr.plane_x * cos(r);
}
