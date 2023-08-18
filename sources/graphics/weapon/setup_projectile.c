/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_projectile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:26:05 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/18 15:47:48 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	initialize_projectile(t_play *player, t_prj *projectile,
	size_t *weapon_frame)
{
	if (player->stat.get[AMMO] <= 0)
		return ;
	projectile->posi.x = player->posi.x;
	projectile->posi.y = player->posi.y;
	projectile->direction.x = player->dir.x;
	projectile->direction.y = player->dir.y;
	projectile->status = true;
	player->stat.get[AMMO]--;
	(*weapon_frame) = 1;
}

void	clear_projectile(t_prj *projectile)
{
	projectile->posi.x = 0.0;
	projectile->posi.y = 0.0;
	projectile->direction.x = 0.0;
	projectile->direction.y = 0.0;
	projectile->status = false;
}
