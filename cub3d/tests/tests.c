/*
** Вставить в main.c.
*/

/* Печать даннх */
printf("R_w: %d|\nR_h: %d|\nNO: %s|\nSO: %s|\nWE: %s|\nEA: %s|\nS: %s|\nfloore_r: %d|\nfloore_g: %d|\nfloore_B: %d|\nceilling_r: %d|\nceilling_g: %d|\nceilling_b: %d|\nsize_map: %d|\ndir: %f|\n", cub.p.resolution_w, cub.p.resolution_l, cub.p.north_texture, cub.p.south_texture, cub.p.west_texture, cub.p.east_texture, cub.p.sprite_texture, cub.p.floore_r, cub.p.floore_g, cub.p.floore_b, cub.p.ceilling_r, cub.p.ceilling_g, cub.p.ceilling_b, cub.p.size_map, cub.plr.dir);

/* Печать индекса игрока */
printf("Player is here: y:%d x:%d\n", cub.p.playr_y, cub.p.playr_x);

/* Печать карты */
int i = -1;
while (cub.p.map[++i])
    ft_putendl_fd(cub.p.map[i], 1);