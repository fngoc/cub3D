#include "../cub3d.h"

/*
** fill_screen: заполнить скриншот.
*/

static	void	fill_screen(int fd, t_cub *cub)
{
	int i;
	int j;
	int color;

	i = cub->p.res_l;
	while (--i >= 0)
	{
		j = -1;
		while (++j < cub->p.res_w)
		{
			color = get_pixel(&cub->data, j, i);
			write(fd, &color, 4);
		}
	}
	exit(0);
}

/*
** screenshot_norm_two: функция для нормы.
*/

static	void	screenshot_norm_two(int fd, int all_pix, int zero, int size)
{
	write(fd, &zero, 4);
	write(fd, &size, 4);
	all_pix = 1000;
	write(fd, &all_pix, 4);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}

/*
** screenshot_norm_one: функция для нормы.
*/

static	void	screenshot_norm_one(int fd)
{
	short	plane;

	plane = 1;
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
}

/*
** screenshot: сделать скриншот.
*/

void			screenshot(t_cub *cub)
{
	int		fd;
	int		all_pix;
	int		zero;
	int		pos_pix;
	int		size;

	fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
	all_pix = cub->p.res_w * cub->p.res_l * 4 + 54;
	zero = 0;
	pos_pix = 54;
	size = cub->p.res_w * cub->p.res_l;
	write(fd, "BM", 2);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pix, 4);
	pos_pix = 40;
	write(fd, &pos_pix, 4);
	write(fd, &cub->p.res_w, 4);
	write(fd, &cub->p.res_l, 4);
	screenshot_norm_one(fd);
	screenshot_norm_two(fd, all_pix, zero, size);
	fill_screen(fd, cub);
}
