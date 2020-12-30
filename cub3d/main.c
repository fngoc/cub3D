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
	t_list		*lst_map;

	lst_map = NULL;
	mlx = NULL;
	win = NULL;
	checking_errors_arg(argc, argv);
	parser(argv, &p, lst_map);
	checking_errors_map(lst_map);
	start(mlx, win, &p);

	return (0);
}