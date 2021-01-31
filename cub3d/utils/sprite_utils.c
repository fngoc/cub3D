#include "../cub3d.h"

/*
** save_position_sprites: сохранить позицию спрайтов
** и вернуть их количество.
*/

void     save_position_sprites(t_cub *cub)
{
    int i;
    int j;
    int coll;

    i = 0;
    coll = 0;
    while (cub->p.map[i] != NULL)
    {
        j = 0;
        while (cub->p.map[i][j] != '\0')
        {
            if (cub->p.map[i][j] == 'B')
            {
                cub->x[coll] = j + 0.5;
                cub->y[coll] = i + 0.5;
                coll++;
            }
            ++j;
        }
        ++i;
    }
}

int     save_position_sprites2(t_cub *cub)
{
    int i;
    int j;
    int coll;

    i = 0;
    coll = 0;
    while (cub->p.map[i] != NULL)
    {
        j = 0;
        while (cub->p.map[i][j] != '\0')
        {
            if (cub->p.map[i][j] == 'B')
                coll++;
            ++j;
        }
        ++i;
    }
    return (coll);
}

/*
** swap_sprite: переместить местами спрайты.
*/

// void    swap_sprite(t_cub *cub, int *j)
// {
//     float tmp;

    
// }

/*
** bubble_sort: сортировка метод "пузырька".
*/

// void    bubble_sort(t_cub *cub)
// {
//     int i;
//     int j;
//     float tmp;

//     i = 0;
//     while (i < cub->p.coll_sprite)
//     {
//         j = 0;
//         while (j < cub->p.coll_sprite)
//         {
//             if (cub->dist[j - 1] < cub->dist[j])
//             {
//                 tmp = cub->dist[j -1];
//                 cub->dist[j -1] = cub->dist[j];
//                 cub->dist[j] = tmp;
//                 tmp = cub->x[j -1];
//                 cub->x[j -1] = cub->x[j];
//                 cub->x[j] = tmp;
//                 tmp = cub->y[j -1];
//                 cub->y[j -1] = cub->y[j];
//                 cub->y[j] = tmp;
//             }
//             ++j;
//         }
//         ++i;
//     }
// }

/*
** sort_sprite: сортировка спрайтов.
*/

void    sort_sprite(t_cub *cub)
{
    int i;

    i = -1;
    while (++i < cub->p.coll_sprite)
        cub->dist[i] = ((cub->plr.x - cub->x[i]) * (cub->plr.x - cub->x[i]) + (cub->plr.y - cub->y[i]) * (cub->plr.y - cub->y[i]));
    // i = -1;
    // while (++i < cub->p.coll_sprite)
    //     printf("%f\n", cub->dist[i]);
    // bubble_sort(cub);
}
