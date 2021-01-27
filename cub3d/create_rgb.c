#include "cub3d.h"

/*
** create_trgb: преобразование RGB в hex.
*/

int create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}