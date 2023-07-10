/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:02 by emis              #+#    #+#             */
/*   Updated: 2023/07/10 05:12:32 by nicolas          ###   ########.fr       */
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

static void	check_and_move_player(t_gui *gui, t_vect dxdy, double magn,
	double magn_target)
{
	t_vect	xy_1;
	t_vect	xy_2;

	xy_1.x = gui->cam.posi.x;
	xy_1.x += dxdy.x * magn_target * gui->cam.sprint_multiplicator;
	xy_1.y = gui->cam.posi.y;
	xy_2.x = gui->cam.posi.x;
	xy_2.y = gui->cam.posi.y;
	xy_2.y += dxdy.y * magn_target * gui->cam.sprint_multiplicator;
	if (gui->map.map[(int)xy_1.x][(int)xy_1.y] == floor_tile)
		gui->cam.posi.x += dxdy.x * magn;
	if (gui->map.map[(int)xy_2.x][(int)xy_2.y] == floor_tile)
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
