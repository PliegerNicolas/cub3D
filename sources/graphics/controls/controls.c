/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:02 by emis              #+#    #+#             */
/*   Updated: 2023/07/10 17:09:00 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	zoom(t_play *player, double dir)
{
	double	target_zoom;

	target_zoom = player->zoom + player->zoom_rate * dir;
	if (target_zoom > 0.5 && target_zoom < 3.0)
		player->zoom = target_zoom;
}

void	pitch(t_play *player, double dir)
{
	player->pitch += dir * player->rotation_speed.y * 500;
}

void	rotate(t_play *player, double dir)
{
	double	rot_speed;
	double	prev_x;

	rot_speed = player->rotation_speed.x * dir;
	prev_x = player->dir.x;
	player->dir.x = player->dir.x * cos(rot_speed)
		- player->dir.y * sin(rot_speed);
	player->dir.y = prev_x * sin(rot_speed)
		+ player->dir.y * cos(rot_speed);
	prev_x = player->plane.x;
	player->plane.x = player->plane.x * cos(rot_speed)
		- player->plane.y * sin(rot_speed);
	player->plane.y = prev_x * sin(rot_speed)
		+ player->plane.y * cos(rot_speed);
}

static void	check_and_move_player(t_map map, t_play *player)
{
	double	target_x;
	double	target_y;

	target_x = player->posi.x + player->speed.x * player->dir.x;
	if (map.map[(int)target_x][(int)player->posi.y] % DOOR_OPEN == floor_tile)
		player->posi.x += player->speed.x * player->dir.x;
	target_y = player->posi.y + player->speed.x * player->dir.y;
	if (map.map[(int)player->posi.x][(int)target_y] % DOOR_OPEN == floor_tile)
		player->posi.y += player->speed.x * player->dir.y;
	target_x = player->posi.x + player->speed.y * player->plane.x;
	if (map.map[(int)target_x][(int)player->posi.y] % DOOR_OPEN == floor_tile)
		player->posi.x += player->speed.y * player->plane.x;
	target_y = player->posi.y + player->speed.y * player->plane.y;
	if (map.map[(int)player->posi.x][(int)target_y] % DOOR_OPEN == floor_tile)
		player->posi.y += player->speed.y * player->plane.y;
}

void	move(t_gui *gui)
{
	check_and_move_player(gui->map, &gui->cam);
}
