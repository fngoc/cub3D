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
            color = *(int*)(cub->data.addr + (i * cub->data.line_length
            + j * (cub->data.bits_per_pixel / 8)));
            write(fd, &color, 4);
        }
    }
    exit(0);
}

/*
** screenshot: сделать скриншот.
*/

void			screenshot(t_cub *cub)
{
    int fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
    int all_pix = cub->p.res_w * cub->p.res_l * 4 + 54;
    int zero = 0;
    int pos_pix = 54;
    short plane = 1;
    int size = cub->p.res_w * cub->p.res_l;

    write(fd, "BM", 2);
    write(fd, &all_pix, 4);
    write(fd, &zero, 4);
    write(fd, &pos_pix, 4);
    pos_pix = 40;
    write(fd, &pos_pix, 4);
    write(fd, &cub->p.res_w, 4);
    write(fd, &cub->p.res_l, 4);
    write(fd, &plane, 2);
    plane = 32;
    write(fd, &plane, 2);
    write(fd, &zero, 4);
    write(fd, &size, 4);
    all_pix = 1000;
    write(fd, &all_pix, 4);
    write(fd, &all_pix, 4);
    write(fd, &zero, 4);
    write(fd, &zero, 4);
    fill_screen(fd, cub);
}