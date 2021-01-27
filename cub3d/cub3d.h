/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:36:05 by fngoc             #+#    #+#             */
/*   Updated: 2021/01/18 16:08:40 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "libs/libft/libft.h"
# include "libs/minilibx_mms/mlx.h"
# include <math.h> /* Для sin и cos */
# include <fcntl.h> /* Для open */
# include <stdio.h> /* Для printf */

# define SCALE 16
# define PI 3.14159265359

/*
** t_parser: структура парсера.
*/

typedef	struct	s_parser
{
	int				resolution_w;
	int				resolution_l;

	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;

	char			*sprite_texture; 

	int				floore_r;
	int				floore_g;
	int				floore_b;
	int				floore_flag;

	int				ceilling_r;
	int				ceilling_g;
	int				ceilling_b;
	int				ceilling_flag;

	char			**map;

	char			*playr;
	int				playr_x;
	int				playr_y;

	int				size_map;
}					t_parser;

/*
** t_point_print: структура печати карты.
*/

typedef struct		s_point_print
{
	double			x;
	double			y;
}					t_point_print;

/*
** t_plr: структура игрока.
*/

typedef struct		s_plr
{
	double			x;
	double			y;
	double			dir;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			start;
	double			end;
}					t_plr;

/*
** t_data: структура данных mlx.
*/

typedef	struct		s_data
{
    void			*img;
    char			*addr;
    int				bits_per_pixel;
    int				line_length;
    int				endian;
}					t_data;

/*
** t_cub: структура в которой находится все.
*/

typedef struct		s_cub
{
	void			*mlx;
	void			*mlx_win;
	t_parser		p;
	t_data			texture;
	t_data			data;
	t_point_print	point;
	t_plr			plr;
}					t_cub;

void				check_errors_arg(int ac, char **av, t_cub *cub);

void				parser(char **argv, t_cub *cub);

void				parser_map(int fd, t_cub *cub);

void				check_all_data(t_cub *cub);

void				check_tab_in_r_f(char *line, t_cub *cub);

void				check_tab(char *line, t_cub *cub);

void				check_c(t_cub *cub);

void				check_f(t_cub *cub);

void				check_r(t_cub *cub);

void				all_tab_in_line(char *str, t_cub *cub);

void				check_symbols_map(int size, t_cub *cub);

void				get_floore(char *tmp, t_cub *cub);

void				get_ceilling(char *tmp, t_cub *cub);

void				start_cub2d(t_cub *cub);

void				start_cub3d(t_cub *cub);

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);

void				error(char *str, t_cub *cub);

int					close_win(t_cub *cub);

int					create_rgb(int r, int g, int b);

unsigned int		get_pixel(t_data *data, int x, int y);

#endif
