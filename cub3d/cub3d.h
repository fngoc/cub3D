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
# include <fcntl.h> /* Для open */
# include <stdio.h> /* Для printf */
# define SCALE 16

typedef	struct		s_parser
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

typedef	struct		s_data
{
    void			*img;
    char			*addr;
    int				bits_per_pixel;
    int				line_length;
    int				endian;
}               	t_data;

typedef struct		s_point_print
{
	int				x;
	int				y;
}					t_point_print;

typedef struct		s_cub3d
{
	void			*mlx;
	void			*mlx_win;
	t_parser		p;
	t_data			data;
	t_point_print	point;
}					t_cub3d;

void				check_errors_arg(int ac, char **av);

void				parser(char **argv, t_parser *p);

void				parser_map(int fd, t_parser *p);

void				check_all_data(t_parser *p);

void				check_tab_in_r_f(char *line);

void				check_tab(char *line);

void				check_c(t_parser *p);

void				check_f(t_parser *p);

void				check_r(t_parser *p);

void				all_tab_in_line(char *str);

void				check_symbols_map(int size, t_parser *p);

void				get_floore(char *tmp, t_parser *p);

void				get_ceilling(char *tmp, t_parser *p);

void				start(t_cub3d *cub3d);

void				error(char *str);

#endif
