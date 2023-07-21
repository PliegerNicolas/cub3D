/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_fov.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 05:46:33 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/21 05:49:58 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

double	calculate_fov(t_play *player)
{
	double	dir_length;
	double	plane_length;
	double	dot_product;
	double	fov_degrees;

	dir_length = sqrt(player->dir.x * player->dir.x
			+ player->dir.y * player->dir.y);
	plane_length = sqrt(player->plane.x * player->plane.x
			+ player->plane.y * player->plane.y);
	dot_product = (player->dir.x * player->plane.x
			+ player->dir.y * player->plane.y);
	fov_degrees = acos(dot_product / (dir_length
				* plane_length)) * (180.0 / M_PI);
	return (fov_degrees);
}
