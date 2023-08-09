/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_projectile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:26:05 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/09 10:37:43 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static t_vect	get_normed_dir(t_play *player)
{
	t_vect	dir;
	double	dir_magnitude;

	dir.x = player->dir.x;
	dir.y = player->dir.y;
	dir.z = sin(player->dir.z);
	dir_magnitude = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	if (dir_magnitude)
	{
		dir.x /= dir_magnitude;
		dir.y /= dir_magnitude;
		dir.z /= dir_magnitude;
	}
	dir.z = (dir.z + 1.5) / 3.0;
	return (dir);
}

void	initialize_projectile(t_play *player, t_prj *projectile)
{
	t_vect	normed_dir;
	double	horizontal_offset;
	double	vertical_offset;

	horizontal_offset = 0.1;
	vertical_offset = 0.1;
	normed_dir = get_normed_dir(player);
	projectile->posi.x = player->posi.x + horizontal_offset * normed_dir.y;
	projectile->posi.y = player->posi.y - horizontal_offset * normed_dir.x;
	projectile->posi.z = normed_dir.z - vertical_offset;
	projectile->direction.x = player->dir.x;
	projectile->direction.y = player->dir.y;
	projectile->direction.z = player->posi.z;
	projectile->status = true;
}

void	clear_projectile(t_prj *projectile)
{
	projectile->posi.x = 0.0;
	projectile->posi.y = 0.0;
	projectile->posi.z = 0.0;
	projectile->direction.x = 0.0;
	projectile->direction.y = 0.0;
	projectile->direction.z = 0.0;
	projectile->status = false;
	printf("\n\n\n");
}
