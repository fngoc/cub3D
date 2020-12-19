#include "cub3d.h"

/*
** Структура проекта: Парсер -> Карта -> Игрок ->
** Клавиатура -> Рейкастинг -> текстуры и предметы.
*/

int main(int argc, char **argv)
{
	t_parser	p;
	t_list		*lst_map;

	lst_map = NULL;
	if (checking_errors(argc, argv))
		return (0);
	parser(argv, &p, lst_map);
	return (0);
}