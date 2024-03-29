#include "../cub3d.h"

/*
** set_dir_plr_norm: функция для нормы.
*/

static	void	set_dir_plr_norm(t_cub *cub)
{
	if (cub->plr.dir_symbol == 'W')
	{
		cub->plr.dir_y = 0;
		cub->plr.dir_x = -1;
		cub->plr.plane_y = -0.66;
		cub->plr.plane_x = 0;
	}
	else if (cub->plr.dir_symbol == 'E')
	{
		cub->plr.dir_y = 0;
		cub->plr.dir_x = 1;
		cub->plr.plane_y = 0.66;
		cub->plr.plane_x = 0;
	}
}

/*
** set_dir_plr: установка направления персонажа.
*/

void			set_dir_plr(t_cub *cub)
{
	if (cub->plr.dir_symbol == 'N')
	{
		cub->plr.dir_y = -1;
		cub->plr.dir_x = 0;
		cub->plr.plane_y = 0;
		cub->plr.plane_x = 0.66;
	}
	else if (cub->plr.dir_symbol == 'S')
	{
		cub->plr.dir_y = 1;
		cub->plr.dir_x = 0;
		cub->plr.plane_y = 0;
		cub->plr.plane_x = -0.66;
	}
	else
		set_dir_plr_norm(cub);
}
