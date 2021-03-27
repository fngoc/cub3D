# cub3D

## Описание

Этот проект вдохновлен первой FPS в истории - Wolfenstein 3D. Наша цель: исследовать проброс лучей, сделать динамический вид внутри лабиринта, в котором мы должны будем найти свой путь.

Компилирование было выполнено следующем образом: ``gcc -Wall -Wextra -Werror *.o -L. -lmlx -lft -framework OpenGL -framework AppKit -o cub3d``.

Все файлы проходят на ``Norminette``.

<p align="center">
  <img src="media/screenshot_from_the_game.png"/>
</p>

## Использование

``make`` и ``make all`` компилируют библиотеку ``libfе.a`` и ``libmlx.dylib``, помещая их в корневую папку.

``make re`` удаляет все ``.o`` файлы, удаляет ``libfе.a`` и ``libmlx.dylib``, пересобирает проект.

``make clean`` удаляет все ``.o`` файлы.

``make fclean`` удаляет все ``.o`` файлы, так же удаляет ``libfе.a`` и ``libmlx.dylib``.

Запуск программы: ``./cub3D [карта]``.

Сделать скриншот: ``./cub3D [карта] --save``.

## Оценка

![alt tag](media/appraisal_cub3D.png "Оценка проекта cub3D")

## my_test

Вставляем код из ``tests.c`` в ``main.c``, компилируем, смотрим на результат.
