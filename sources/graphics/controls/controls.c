/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:02 by emis              #+#    #+#             */
/*   Updated: 2023/08/09 17:10:13 by nplieger         ###   ########.fr       */
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
	double	target_pitch;

	target_pitch = player->pitch + dir * player->rot_speed.y;
	if (target_pitch >= -(90 * (M_PI / 180.0))
		&& target_pitch <= (90 * (M_PI / 180.0)))
		player->pitch = target_pitch;
}

void	rotate(t_play *player, double dir)
{
	double	rot_speed;
	double	prev_x;

	rot_speed = player->rot_speed.x * dir;
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
	t_vect	forward_step;
	t_vect	lateral_step;
	t_vect	next_pos;

	forward_step.x = player->speed.x * player->dir.x;
	lateral_step.x = player->speed.x * player->dir.y;
	forward_step.y = player->speed.y * player->plane.x;
	lateral_step.y = player->speed.y * player->plane.y;
	next_pos.x = player->posi.x + forward_step.x + forward_step.y;
	next_pos.y = player->posi.y + lateral_step.x + lateral_step.y;
	if (map.map[(int)next_pos.x][(int)player->posi.y] % DOOR_OPEN == floor_tile)
		player->posi.x += forward_step.x + forward_step.y;
	if (map.map[(int)player->posi.x][(int)next_pos.y] % DOOR_OPEN == floor_tile)
		player->posi.y += lateral_step.x + lateral_step.y;
}

void	move(t_gui *gui)
{
	check_and_move_player(gui->map, &gui->cam);
}
