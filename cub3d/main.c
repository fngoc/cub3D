#include "cub3d.h"

/*
** Структура проекта: Парсер -> Карта -> Игрок ->
** Клавиатура -> Рейкастинг -> текстуры и предметы.
*/

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	t_parser	p;

	mlx = NULL;
	win = NULL;
	checking_errors_arg(argc, argv);
	parser(argv, &p);
	checking_errors_map(&p);
	start(mlx, win, &p);
	return (0);
}