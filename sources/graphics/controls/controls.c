/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:02 by emis              #+#    #+#             */
/*   Updated: 2023/07/08 09:05:57 by nicolas          ###   ########.fr       */
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
	t_vect	hit_box;
	double	added_x;
	double	added_y;
	int		x;
	int		y;

	added_x = dxdy.x * magn;
	added_y = dxdy.y * magn;
	hit_box.x = 0.15;
	hit_box.y = 0.15;
	if (added_x < 0.0)
		hit_box.x = -hit_box.x;
	if (added_y < 0.0)
		hit_box.y = -hit_box.y;
	x = posi->x + hit_box.x + added_x;
	y = posi->y;
	if (map.map[x][y] == floor_tile)
		posi->x += added_x;
	x = posi->x;
	y = posi->y + hit_box.y + added_y;
	if (map.map[x][y] == floor_tile)
		posi->y += added_y;
}

void	move(t_gui *gui)
{
	check_and_move(gui->map, &gui->cam.posi, gui->cam.dir, gui->cam.speed.x);
	check_and_move(gui->map, &gui->cam.posi, gui->cam.plane, gui->cam.speed.y);
	printf("x = %f y = %f\n", gui->cam.speed.x, gui->cam.speed.y);
}
