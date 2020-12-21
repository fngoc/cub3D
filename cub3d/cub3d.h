#ifndef CUB3D_H

# define CUB3D_H

# include "libs/libft/libft.h"
# include <fcntl.h> /* Для open */
# include <stdio.h> /* Для printf */

typedef struct	s_parser
{
	int resolution_w;
	int resolution_l;

	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;

	char *sprite_texture;

	int floore_R;
	int floore_G;
	int floore_B;

	int ceilling_R;
	int ceilling_G;
	int ceilling_B;
}				t_parser;

void	checking_errors(int ac, char **av);

void	parser(char **argv, t_parser *p, t_list	*lst_map);

#endif
