/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 23:54:23 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/04 15:23:35 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** malloc_arrays: выделение памяти под масив спрайтов.
*/

static	void	malloc_arrays(t_cub *cub)
{
    if (!(cub->x = malloc(sizeof(float) * cub->p.coll_sprite)))
        error("ERROR: No memory allocated", cub);
    if (!(cub->y = malloc(sizeof(float) * cub->p.coll_sprite)))
        error("ERROR: No memory allocated", cub);
    if (!(cub->dist = malloc(sizeof(float) * cub->p.coll_sprite)))
        error("ERROR: No memory allocated", cub);
    if (!(cub->close_sprite = malloc(sizeof(double) * cub->p.res_w)))
        error("ERROR: No memory allocated", cub);
}

/*
** print_sprite: печать спрайта.
*/

static	void	print_sprite(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < cub->p.coll_sprite)
	{
		//перевести положение спрайта относительно камеры
		double spriteX = cub->x[i] - cub->plr.x;
		double spriteY = cub->y[i] - cub->plr.y;

		//требуется для правильного умножения матриц
		double invDet = 1.0 / (cub->plr.planeX * cub->plr.dirY - cub->plr.dirX * cub->plr.planeY);

		double transformX = invDet * (cub->plr.dirY * spriteX - cub->plr.dirX * spriteY);

		//это на самом деле глубина внутри экрана, то, что Z есть в 3D
		double transformY = invDet * (-cub->plr.planeY * spriteX + cub->plr.planeX * spriteY); 

		int spriteScreenX = (int)((cub->p.res_w / 2) * (1 + transformX / transformY));

		//вычислите высоту спрайта на экране
		int spriteHeight = abs((int)(cub->p.res_l / (transformY))); //с помощью transformY' вместо реального расстояния предотвращает рыбий глаз
		//вычислите самый низкий и самый высокий пиксель для заполнения текущей полосы
		int drawStartY = -spriteHeight / 2 + cub->p.res_l / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + cub->p.res_l / 2;
		if (drawEndY >= cub->p.res_l)
			drawEndY = cub->p.res_l - 1;

		//вычислить ширину спрайта
		int spriteWidth = abs((int)(cub->p.res_l / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0) drawStartX = 0;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= cub->p.res_w)
			drawEndX = cub->p.res_w - 1;

		//петля через каждую вертикальную полосу спрайта на экране
		int stripe;
		int y;

		stripe = drawStartX;
		while (stripe < drawEndX)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXWIDTH / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < cub->p.res_w && transformY < cub->close_sprite[stripe])
			{
				y = drawStartY;
				while (y < drawEndY) //для каждого пикселя текущей полосы
				{
					int d = (y) * 256 - cub->p.res_l * 128 + spriteHeight * 128;
					int texY = ((d * TEXHEIGHT) / spriteHeight) / 256;
					int color = get_pixel(&cub->t_spr, texX, texY);
					if (color != 0)
						my_mlx_pixel_put(&cub->data, stripe, y, color);
					y++;
				}
			}
			++stripe;
		}
	}
}

/*
** side_world_norm: функция для нормы.
*/

void	side_world_norm(t_norm_print_map *n, t_cub *cub, int *x, int *y)
{
	n->tex_y = (int)n->tex_pos & (TEXHEIGHT - 1);
	n->tex_pos += n->step;
	if (n->side == 0)
	{
		if (n->step_x > 0)
			my_mlx_pixel_put(&cub->data, *x, *y,
			get_pixel(&cub->t_s, n->tex_x, n->tex_y));
		else
			my_mlx_pixel_put(&cub->data, *x, *y,
			get_pixel(&cub->t_n, n->tex_x, n->tex_y));
	}
	else
	{
		if (n->step_y > 0)
			my_mlx_pixel_put(&cub->data, *x, *y,
			get_pixel(&cub->t_e, n->tex_x, n->tex_y));
		else
			my_mlx_pixel_put(&cub->data, *x, *y,
			get_pixel(&cub->t_w, n->tex_x, n->tex_y));
	}
}

/*
** side_world: функция для нормы.
*/

void	side_world(t_norm_print_map *n, t_cub *cub, int *x, int *y)
{
	if (*y < n->draw_start)
		my_mlx_pixel_put(&cub->data, *x, *y,
		create_rgb(cub->p.ceilling_r, cub->p.ceilling_g, cub->p.ceilling_b));
	if (*y >= n->draw_start && *y <= n->draw_end)
		side_world_norm(n, cub, x, y);
	if (*y > n->draw_end && *y < cub->p.res_l)
		my_mlx_pixel_put(&cub->data, *x, *y,
		create_rgb(cub->p.floore_r, cub->p.floore_g, cub->p.floore_b));
}

/*
** calc_more: функция для нормы.
*/

void	calc_more(t_norm_print_map *n, t_cub *cub, int *x)
{
	if (n->side == 0)
		n->perp_wall_dist = (n->map_x - cub->plr.y
			+ (1 - n->step_x) / 2) / n->ray_dir_x;
	else
		n->perp_wall_dist = (n->map_y - cub->plr.x
			+ (1 - n->step_y) / 2) / n->ray_dir_y;
	cub->close_sprite[*x] = n->perp_wall_dist;
	n->line_height = (int)(cub->p.res_l / n->perp_wall_dist);
	n->draw_start = -n->line_height / 2 + cub->p.res_l / 2;
	if (n->draw_start < 0)
		n->draw_start = 0;
	n->draw_end = n->line_height / 2 + cub->p.res_l / 2;
	if (n->draw_end >= cub->p.res_l)
		n->draw_end = cub->p.res_l - 1;
	if (n->side == 0)
		n->wall_x = cub->plr.x + n->perp_wall_dist * n->ray_dir_y;
	else
		n->wall_x = cub->plr.y + n->perp_wall_dist * n->ray_dir_x;
	n->wall_x -= floor((n->wall_x));
	n->tex_x = (int)(n->wall_x * (double)(TEXWIDTH));
	if (n->side == 0 && n->ray_dir_x > 0)
		n->tex_x = TEXWIDTH - n->tex_x - 1;
	if (n->side == 1 && n->ray_dir_y < 0)
		n->tex_x = TEXWIDTH - n->tex_x - 1;
}

/*
** check_hit: функция для нормы.
*/

void	check_hit(t_norm_print_map *n, t_cub *cub)
{
	if (n->side_dist_x < n->side_dist_y)
	{
		n->side_dist_x += n->delta_dist_x;
		n->map_x += n->step_x;
		n->side = 0;
	}
	else
	{
		n->side_dist_y += n->delta_dist_y;
		n->map_y += n->step_y;
		n->side = 1;
	}
	if (cub->p.map[n->map_x][n->map_y] == '1')
		n->hit = 1;
}

/*
** calc_step_start: функция для нормы.
*/

void	calc_step_start(t_norm_print_map *n, t_cub *cub)
{
	if (n->ray_dir_x < 0)
	{
		n->step_x = -1;
		n->side_dist_x = (cub->plr.y - n->map_x) * n->delta_dist_x;
	}
	else
	{
		n->step_x = 1;
		n->side_dist_x = (n->map_x + 1.0 - cub->plr.y) * n->delta_dist_x;
	}
	if (n->ray_dir_y < 0)
	{
		n->step_y = -1;
		n->side_dist_y = (cub->plr.x - n->map_y) * n->delta_dist_y;
	}
	else
	{
		n->step_y = 1;
		n->side_dist_y = (n->map_y + 1.0 - cub->plr.x) * n->delta_dist_y;
	}
}

/*
** set_cam_ray_mapxy: функция для нормы.
*/

void	set_cam_ray_mapxy(t_norm_print_map *n, int *x, t_cub *cub)
{
	n->camera_x = 2 * *x / (double)cub->p.res_w - 1;
	n->ray_dir_x = cub->plr.dirY + cub->plr.planeY * n->camera_x;
	n->ray_dir_y = cub->plr.dirX + cub->plr.planeX * n->camera_x;
	n->map_x = (int)(cub->plr.y);
	n->map_y = (int)(cub->plr.x);
	n->delta_dist_x = sqrt(1 + (n->ray_dir_y * n->ray_dir_y)
							/ (n->ray_dir_x * n->ray_dir_x));
	n->delta_dist_y = sqrt(1 + (n->ray_dir_x * n->ray_dir_x)
							/ (n->ray_dir_y * n->ray_dir_y));
	n->hit = 0;
}

/*
** print_map: печать карты.
*/

static	void	print_map(t_cub *cub)
{
	t_norm_print_map	n;
	int					x;
	int					y;

	cub->data.img = mlx_new_image(cub->mlx, cub->p.res_w, cub->p.res_l);
	cub->data.addr = mlx_get_data_addr(cub->data.img,
	&cub->data.bits_per_pixel, &cub->data.line_length, &cub->data.endian);
	x = -1;
	while (++x < cub->p.res_w)
	{
		set_cam_ray_mapxy(&n, &x, cub);
		calc_step_start(&n, cub);
		while (n.hit == 0)
			check_hit(&n, cub);
		calc_more(&n, cub, &x);
		n.step = 1.0 * TEXHEIGHT / n.line_height;
		n.tex_pos = (n.draw_start - cub->p.res_l
				/ 2 + n.line_height / 2) * n.step;
		y = -1;
		while (++y < cub->p.res_l)
			side_world(&n, cub, &x, &y);
	}
	sort_sprite(cub);
	print_sprite(cub);
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->data.img, 0, 0);
}

/*
** key_hook: взаимодействие с клавиатурой.
*/

static	int		key_hook(int keycode, t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->data.img);
	if (keycode == 13)
		move_up(cub, 0.1);
	if (keycode == 1)
		move_back(cub, 0.1);
	if (keycode == 0)
		move_left(cub, 0.1);
	if (keycode == 2)
		move_right(cub, 0.1);
	if (keycode == 124)
		turn_right(cub, 0.1);
	if (keycode == 123)
		turn_left(cub, 0.1);
	if (keycode == 48)
		system("afplay ./sounds/minecraft-death-sound.mp3 & ");
	if (keycode == 53)
		close_win(cub);
	print_map(cub);
	return (0);
}

/*
** start_cub3d: запуск окна, работа в 3D.
*/

void				start_cub3d(t_cub *cub, int argc)
{
	cub->plr.y = (double)cub->p.playr_y + 0.5;
	cub->plr.x = (double)cub->p.playr_x + 0.5;
	cub->p.coll_sprite = counting_sprites(cub);
	malloc_arrays(cub);
	save_position_sprites(cub);
	set_dir_plr(cub);
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, cub->p.res_w,
									cub->p.res_l, "cub3d");
	get_sprite(cub);
	print_map(cub);
	if (argc == 3)
		screenshot(cub);
	else
	{
		// system("afplay ./sounds/C418-Door.mp3 & ");
		mlx_hook(cub->mlx_win, 2, 1L << 0, key_hook, cub);
		mlx_hook(cub->mlx_win, 17, 1L << 0, close_win, cub);
		mlx_loop(cub->mlx);
	}
}
