/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 06:49:04 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/09 06:49:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	check_and_move(t_map map, t_vect *posi, t_vect dxdy, double magn)
{
	t_vect	xy_1;
	t_vect	xy_2;

	xy_1.x = posi->x + dxdy.x * magn;
	xy_1.y = posi->y;
	xy_2.x = posi->x;
	xy_2.y = posi->y + dxdy.y * magn;
	if (map.map[(int)xy_1.x][(int)xy_1.y] == floor_tile)
		posi->x += dxdy.x * magn;
	if (map.map[(int)xy_2.x][(int)xy_2.y] == floor_tile)
		posi->y += dxdy.y * magn;
}
