#ifndef CUB3D_H

# define CUB3D_H

# include "libs/libft/libft.h"
# include "libs/minilibx_mms/mlx.h"
# include <fcntl.h> /* Для open */
# include <stdio.h> /* Для printf */

typedef struct	s_parser
{
	int		resolution_w;
	int		resolution_l;

	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;

	char	*sprite_texture;

	int		floore_R;
	int		floore_G;
	int		floore_B;

	int		ceilling_R;
	int		ceilling_G;
	int		ceilling_B;

	char	**map;
}				t_parser;

void	checking_errors_arg(int ac, char **av);

void	parser(char **argv, t_parser *p);

void	parser_map(int fd, t_parser *p);

void	checking_errors_map(t_parser *p);

void	start(void *mlx, void *win, t_parser *p);

#endif
