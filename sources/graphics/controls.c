/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:02 by emis              #+#    #+#             */
/*   Updated: 2023/07/07 19:07:41 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

void	pitch(t_play	*play, int dir)
{
	double pRate = 0.025;

	pRate *= dir;
	play->pitch += 8 * dir;
}

void	rotate(t_play	*play, double dir)
{
	double rotSpeed = 0.05; //frameTime * 3.0 //the constant value is in radians/second

	double oldDirX = play->dir.x;
	rotSpeed *= dir;
	play->dir.x = play->dir.x * cos(rotSpeed) - play->dir.y * sin(rotSpeed);
	play->dir.y = oldDirX * sin(rotSpeed) + play->dir.y * cos(rotSpeed);
	double oldPlaneX = play->plane.x;
	play->plane.x = play->plane.x * cos(rotSpeed) - play->plane.y * sin(rotSpeed);
	play->plane.y = oldPlaneX * sin(rotSpeed) + play->plane.y * cos(rotSpeed);
}

void	check_and_move(t_map map, t_vect *posi, t_vect dxdy, double magn)
{
	if (map.map[(int)(posi->x + dxdy.x * magn)][(int)(posi->y)] % DOOR == 0)
		posi->x += dxdy.x * magn;
	if (map.map[(int)(posi->x)][(int)(posi->y + dxdy.y * magn)] % DOOR == 0)
		posi->y += dxdy.y * magn;
}

int	move(t_gui *gui)
{
	double moveSpeed = 0.20 * gui->cam.speed; //frameTime * 5.0 //the constant value is in squares/second

	if (gui->keys & (1 << KP_forth))
		check_and_move(gui->map, &gui->cam.posi, gui->cam.dir, moveSpeed);
	else if (gui->keys & (1 << KP_back))
		check_and_move(gui->map, &gui->cam.posi, gui->cam.dir, -moveSpeed);
	if (gui->keys & (1 << KP_right))
		check_and_move(gui->map, &gui->cam.posi, gui->cam.plane, moveSpeed);
	else if (gui->keys & (1 << KP_left))
		check_and_move(gui->map, &gui->cam.posi, gui->cam.plane, -moveSpeed);
	return (0);
}
