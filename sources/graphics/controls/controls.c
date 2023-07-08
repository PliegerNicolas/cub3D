/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:02 by emis              #+#    #+#             */
/*   Updated: 2023/07/08 22:31:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	zoom(t_play *player, double dir)
{
	player->zoom_rate *= dir;
	player->zoom += player->zoom_rate;
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


void	check_and_move(t_map map, t_vect *posi, t_vect dxdy, double magn)
{
	int		x;
	int		y;

	x = posi->x + dxdy.x * magn;
	y = posi->y;
	if (map.map[x][y] == floor_tile)
		posi->x += dxdy.x * magn;
	x = posi->x;
	y = posi->y + dxdy.y * magn;
	if (map.map[x][y] == floor_tile)
		posi->y += dxdy.y * magn;
}

static void	check_and_move_player(t_gui *gui, t_vect dxdy, double magn,
	double magn_target)
{
	int		x;
	int		y;

	x = gui->cam.posi.x + dxdy.x * magn_target;
	y = gui->cam.posi.y;
	if (gui->map.map[x][y] == floor_tile)
		gui->cam.posi.x += dxdy.x * magn;
	x = gui->cam.posi.x;
	y = gui->cam.posi.y + dxdy.y * magn_target;
	if (gui->map.map[x][y] == floor_tile)
		gui->cam.posi.y += dxdy.y * magn;
}

void	move(t_gui *gui)
{
	if (gui->cam.speed.x < 0.0)
		check_and_move_player(gui, gui->cam.dir, gui->cam.speed.x,
			-gui->cam.speed_target.x);
	else
		check_and_move_player(gui, gui->cam.dir, gui->cam.speed.x,
			gui->cam.speed_target.x);
	if (gui->cam.speed.y < 0.0)
		check_and_move_player(gui, gui->cam.plane, gui->cam.speed.y,
			-gui->cam.speed_target.y);
	else
		check_and_move_player(gui, gui->cam.plane, gui->cam.speed.y,
			gui->cam.speed_target.y);
}
