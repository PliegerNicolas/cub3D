/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:49:02 by emis              #+#    #+#             */
/*   Updated: 2023/06/16 15:09:49 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

void	rotate(t_play	*play, int dir)
{
	double rotSpeed = 0.1; //frameTime * 3.0 //the constant value is in radians/second

	double oldDirX = play->dir.x;
	rotSpeed *= dir;
	play->dir.x = play->dir.x * cos(rotSpeed) - play->dir.y * sin(rotSpeed);
	play->dir.y = oldDirX * sin(rotSpeed) + play->dir.y * cos(rotSpeed);
	double oldPlaneX = play->plane.x;
	play->plane.x = play->plane.x * cos(rotSpeed) - play->plane.y * sin(rotSpeed);
	play->plane.y = oldPlaneX * sin(rotSpeed) + play->plane.y * cos(rotSpeed);
}

int	move(int keycode, t_gui *gui)
{
	double moveSpeed = 0.25; //frameTime * 5.0 //the constant value is in squares/second

	if (keycode == forth)
	{
		if(gui->map->map[(int)(gui->player.posi.x + gui->player.dir.x * moveSpeed)][(int)(gui->player.posi.y)] == 0) gui->player.posi.x += gui->player.dir.x * moveSpeed;
		if(gui->map->map[(int)(gui->player.posi.x)][(int)(gui->player.posi.y + gui->player.dir.y * moveSpeed)] == 0) gui->player.posi.y += gui->player.dir.y * moveSpeed;
	}
	else if (keycode == back)
	{
		if(gui->map->map[(int)(gui->player.posi.x - gui->player.dir.x * moveSpeed)][(int)(gui->player.posi.y)] == 0) gui->player.posi.x -= gui->player.dir.x * moveSpeed;
		if(gui->map->map[(int)(gui->player.posi.x)][(int)(gui->player.posi.y - gui->player.dir.y * moveSpeed)] == 0) gui->player.posi.y -= gui->player.dir.y * moveSpeed;
	}
	else if (keycode == right)
	{
		if(gui->map->map[(int)(gui->player.posi.x + gui->player.dir.x * moveSpeed)][(int)(gui->player.posi.y)] == 0) gui->player.posi.x += gui->player.plane.x * moveSpeed;
		if(gui->map->map[(int)(gui->player.posi.x)][(int)(gui->player.posi.y + gui->player.dir.y * moveSpeed)] == 0) gui->player.posi.y += gui->player.plane.y * moveSpeed;
	}
	else if (keycode == left)
	{
		if(gui->map->map[(int)(gui->player.posi.x - gui->player.dir.x * moveSpeed)][(int)(gui->player.posi.y)] == 0) gui->player.posi.x -= gui->player.plane.x * moveSpeed;
		if(gui->map->map[(int)(gui->player.posi.x)][(int)(gui->player.posi.y - gui->player.dir.y * moveSpeed)] == 0) gui->player.posi.y -= gui->player.plane.y * moveSpeed;
	}
	else
		return (1);
	return (0);
}

int	key_press(int keycode, t_gui *gui)
{
	if (keycode == XK_Escape)
		mlx_loop_end(gui->mlx);
	else if (keycode == rot_left)
		rotate(&gui->player, -1);
	else if (keycode == rot_right)
		rotate(&gui->player, 1);
	else
		move(keycode, gui);
	return (0);
}

int	key_rel(int keycode, t_gui *gui)
{
	if (keycode && gui->mlx)
		(void)keycode;
	return (0);
}
