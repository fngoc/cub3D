/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_utils_tree.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fngoc <fngoc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 20:04:24 by fngoc             #+#    #+#             */
/*   Updated: 2021/02/06 20:04:26 by fngoc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** check_av_tree: проверка на название '--save'.
*/

int			check_av_tree(char *av)
{
	if (av[0] == '-' && av[1] == '-' && av[2] == 's' &&
	av[3] == 'a' && av[4] == 'v' && av[5] == 'e')
		return (0);
	else
		return (1);
}

/*
** check_av_two: проверка на название 'map.cub'.
*/

int			check_av_two(char *av)
{
	if (av[ft_strlen(av) - 1] == 'b' && av[ft_strlen(av) - 2] == 'u'
	&& av[ft_strlen(av) - 3] == 'c' && av[ft_strlen(av) - 4] == '.'
	&& av[ft_strlen(av) - 5] == 'p' && av[ft_strlen(av) - 6] == 'a'
	&& av[ft_strlen(av) - 7] == 'm')
		return (0);
	else
		return (1);
}

/*
** check_av_one: проверка на название 'map.cub'.
*/

int			check_av_one(char *av)
{
	if (av[0] == 'm' && av[1] == 'a' && av[2] == 'p' &&
	av[3] == '.' && av[4] == 'c' && av[5] == 'u' &&
	av[6] == 'b')
		return (0);
	else
		return (1);
}
