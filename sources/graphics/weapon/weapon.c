/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/25 21:27:04 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	initialize_projectile(t_play *player, t_prj *projectile)
{
	projectile->posi.x = player->posi.x;
	projectile->posi.y = player->posi.y;
	projectile->posi.z = player->posi.z;
	projectile->direction.x = player->dir.x;
	projectile->direction.y = player->dir.y;
	projectile->direction.z = player->posi.z;
	projectile->status = true;
}

static void	clear_projectile(t_prj *projectile)
{
	projectile->posi.x = 0.0;
	projectile->posi.y = 0.0;
	projectile->posi.z = 0.0;
	projectile->direction.x = 0.0;
	projectile->direction.y = 0.0;
	projectile->direction.z = 0.0;
	projectile->status = false;
}

static void	move_projectile(t_prj *projectile)
{
	double	pitch_rad;

	pitch_rad = (fabs(projectile->direction.z) / 1.5) * (M_PI / 180.0);
	projectile->posi.x += projectile->direction.x
			* (double)PROJECTILE_SPEED * cos(pitch_rad);
	projectile->posi.y += projectile->direction.y
			* (double)PROJECTILE_SPEED * cos(pitch_rad);
	projectile->posi.z -= projectile->direction.z
			* (double)PROJECTILE_SPEED * sin(pitch_rad);
}

static void	draw_projectile(t_gui *gui, int x, int y, double distance)
{
	(void)distance;
	pixput(gui->buffer, x, y, 0xFFFFFF);
}

static bool raycast_projectile(t_gui *gui, t_prj *projectile)
{
	t_play	*player;
	double	proj_ray_dir_x;
	double	proj_ray_dir_y;
	double	dot_product;

	player = &gui->cam;
	proj_ray_dir_x = projectile->posi.x - player->posi.x;
	proj_ray_dir_y = projectile->posi.y - player->posi.y;
	dot_product = player->dir.x * proj_ray_dir_x + player->dir.y * proj_ray_dir_y;
	if (dot_product < cos(player->fov / 2))
		return (false);
	double	distance = sqrt(proj_ray_dir_x * proj_ray_dir_x + proj_ray_dir_y * proj_ray_dir_y);
	double	step_x = proj_ray_dir_x / distance;
	double	step_y = proj_ray_dir_y / distance;
	double	current_x = player->posi.x;
	double	current_y = player->posi.y;

	while (current_x < projectile->posi.x && current_y < projectile->posi.y)
	{
		int cell_x = (int)(current_x + 0.5);
        int cell_y = (int)(current_y + 0.5);
		if (gui->map.map[(int)cell_x][(int)cell_y] % DOOR_OPEN != floor_tile)
			return (false);
        current_x += step_x;
    	current_y += step_y;
	}

	double inv_det = 1.0 / (player->plane.x * player->dir.y
			- player->dir.x * player->plane.y);
	double transform_x = inv_det * (player->dir.y * (projectile->posi.x
			- player->posi.x) - player->dir.x * (projectile->posi.y - player->posi.y));
	double transform_y = inv_det * (-player->plane.y
			* (projectile->posi.x - player->posi.x) + player->plane.x
			* (projectile->posi.y - player->posi.y));

	int x = (int)((SCRWIDTH / 2) * (1 + transform_x / transform_y));
	int	y = (int)(SCRHEIGHT / 2) + (SCRHEIGHT * player->posi.z) - (SCRHEIGHT * projectile->posi.z);

	draw_projectile(gui, x, y, distance);

	return (false);
}

static void	attack(t_gui *gui, t_prj *projectile)
{
	move_projectile(projectile);
	raycast_projectile(gui, projectile);
	if (projectile_collision(gui, projectile))
	{
		// draw projectile collision
		clear_projectile(projectile);
	}
	else
	{
		// draw projectile and move forward
		(void)gui;
	}
}

void	weapon(t_gui *gui)
{
	static t_prj	projectile;
	static int		walk_frame;
	int				weapon_x;
	int				weapon_y;

	if (!gui->textures.weapon)
		return ;
	weapon_x = 0;
	weapon_y = 0;
	//draw_crosshair(gui, 0xE4E6Eb);
	walk_frame = calculate_next_walk_frame(gui, walk_frame);
	set_weapon_position(gui, &weapon_x, &weapon_y, walk_frame);
	if (!projectile.status && (gui->btns & (1 << left_click)))
		initialize_projectile(&gui->cam, &projectile);
	if (projectile.status)
		attack(gui, &projectile);
	imgput(gui->buffer, weapon_x, weapon_y, gui->textures.weapon);
}
