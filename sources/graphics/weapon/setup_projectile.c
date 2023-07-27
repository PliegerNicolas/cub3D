/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_projectile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:26:05 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/27 00:26:41 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	initialize_projectile(t_play *player, t_prj *projectile)
{
	projectile->posi.x = player->posi.x;
	projectile->posi.y = player->posi.y;
	projectile->posi.z = player->posi.z;
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
}
