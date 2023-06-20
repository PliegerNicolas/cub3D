/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:02 by emis              #+#    #+#             */
/*   Updated: 2023/06/20 19:24:36 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

void	zoom(t_play	*play, int dir)
{
	double zoomRate = 0.025;

	zoomRate *= dir;
	// play->zoom += zoomRate;
	play->pitch += dir;
}

void	rotate(t_play	*play, int dir)
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

int	move(t_gui *gui)
{
	double moveSpeed = 0.20 * gui->cam.speed; //frameTime * 5.0 //the constant value is in squares/second

	if (gui->keys & (1 << KP_forth))
	{
		if(gui->map->map[(int)(gui->cam.posi.x + gui->cam.dir.x * moveSpeed)][(int)(gui->cam.posi.y)] == 0) gui->cam.posi.x += gui->cam.dir.x * moveSpeed;
		if(gui->map->map[(int)(gui->cam.posi.x)][(int)(gui->cam.posi.y + gui->cam.dir.y * moveSpeed)] == 0) gui->cam.posi.y += gui->cam.dir.y * moveSpeed;
	}
	else if (gui->keys & (1 << KP_back))
	{
		if(gui->map->map[(int)(gui->cam.posi.x - gui->cam.dir.x * moveSpeed)][(int)(gui->cam.posi.y)] == 0) gui->cam.posi.x -= gui->cam.dir.x * moveSpeed;
		if(gui->map->map[(int)(gui->cam.posi.x)][(int)(gui->cam.posi.y - gui->cam.dir.y * moveSpeed)] == 0) gui->cam.posi.y -= gui->cam.dir.y * moveSpeed;
	}
	if (gui->keys & (1 << KP_right))
	{
		if(gui->map->map[(int)(gui->cam.posi.x + gui->cam.plane.x * moveSpeed)][(int)(gui->cam.posi.y)] == 0) gui->cam.posi.x += gui->cam.plane.x * moveSpeed;
		if(gui->map->map[(int)(gui->cam.posi.x)][(int)(gui->cam.posi.y + gui->cam.plane.y * moveSpeed)] == 0) gui->cam.posi.y += gui->cam.plane.y * moveSpeed;
	}
	else if (gui->keys & (1 << KP_left))
	{
		if(gui->map->map[(int)(gui->cam.posi.x - gui->cam.plane.x * moveSpeed)][(int)(gui->cam.posi.y)] == 0) gui->cam.posi.x -= gui->cam.plane.x * moveSpeed;
		if(gui->map->map[(int)(gui->cam.posi.x)][(int)(gui->cam.posi.y - gui->cam.plane.y * moveSpeed)] == 0) gui->cam.posi.y -= gui->cam.plane.y * moveSpeed;
	}
	return (0);
}

int	key_press(int keycode, t_gui *gui)
{
	int	i;

	if (keycode == XK_Escape)
		return (mlx_loop_end(gui->mlx));
	i = -1;
	while ((__u_int)++i < sizeof(KEYS) / sizeof(*KEYS))
		if (keycode == (int)KEYS[i])
			gui->keys |= (1 << i);
	return (0);
}

int	key_rel(int keycode, t_gui *gui)
{
	int	i;

	i = -1;
	while ((__u_int)++i < sizeof(KEYS) / sizeof(*KEYS))
		if (keycode == (int)KEYS[i])
			gui->keys &= ~(1 << i);
	return (0);
}
