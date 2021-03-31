#include "cub3d.h"

/*
** main: запуск программы.
*/

int	main(int argc, char **argv)
{
	t_cub		cub;

	check_errors_arg(argc, argv, &cub);
	parser(argv, &cub);
	start_cub3d(&cub, argc);
	return (0);
}
