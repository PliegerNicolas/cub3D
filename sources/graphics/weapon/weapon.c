/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/08/09 17:00:42 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static double	distance_between_player_and_projectile(t_play *player, t_prj *projectile, t_rc *rc)
{
	double	horizontal_distance;
	double	vertical_distance;
	double	distance;

	horizontal_distance = sqrt(rc->ray_dir.x * rc->ray_dir.x + rc->ray_dir.y * rc->ray_dir.y);
	vertical_distance = fabs(projectile->posi.z - player->pitch);
	distance = sqrt(horizontal_distance * horizontal_distance + vertical_distance * vertical_distance);
	return (distance);
}

static void	move_projectile(t_prj *projectile)
{
	projectile->posi.x += (double)PROJECTILE_SPEED
			* projectile->direction.x;
	projectile->posi.y += (double)PROJECTILE_SPEED
			* projectile->direction.y;
	projectile->posi.z += (double)PROJECTILE_SPEED
			* (projectile->direction.z / 1.5);
}

static void	rays(t_play *p, t_rc *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step_x = -1;
		rc->side_dist.x = (p->posi.x - rc->map_x) * rc->delta_dist.x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist.x = (rc->map_x + 1.0 - p->posi.x) * rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step_y = -1;
		rc->side_dist.y = (p->posi.y - rc->map_y) * rc->delta_dist.y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist.y = (rc->map_y + 1.0 - p->posi.y) * rc->delta_dist.y;
	}
}


static bool	cast(t_gui *gui, t_rc *rc, double distance)
{

	rays(&gui->cam, rc);

	while (distance > 0)
	{
		int	cell_x = (int)rc->map_x;
		int	cell_y = (int)rc->map_y;
		if (gui->map.map[cell_x][cell_y] % DOOR_OPEN != floor_tile)
		{
			return (false);
		}
		// Move to the next intersection point along the ray
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->map_x += rc->step_x;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map_y += rc->step_y;
		}

		// Update the remaining distance
		distance -= 1.0;
	}
	return (true);
}

static void	normalize_ray_dir(t_rc *rc)
{
	double	ray_dir_magnitude;

	ray_dir_magnitude = magnitude(rc->ray_dir);
	if (ray_dir_magnitude)
	{
		rc->ray_dir.x /= ray_dir_magnitude;
		rc->ray_dir.y /= ray_dir_magnitude;
	}
}

static bool	is_in_fov(t_play *player, t_prj *projectile, t_rc rc)
{
	normalize_ray_dir(&rc);
	double	dot_product = player->dir.x * rc.ray_dir.x + player->dir.y * rc.ray_dir.y;
	if (dot_product < 0.5)
		return (false);

	double vertical_angle = atan2(projectile->direction.z, magnitude(rc.ray_dir));
	double max_pitch = 1.5; // Adjust this value as needed
	double max_allowed_vertical_angle = max_pitch / 2.0;

	// Compare the vertical angle with the player's pitch angle
	if (fabs(vertical_angle - player->pitch) > max_allowed_vertical_angle)
		return (false);
	return (true);
}

static bool raycast_projectile(t_gui *gui, t_prj *projectile)
{
	t_rc	rc;

	// Get the player's coordinates relative to the grid (convert to int and round down)
	rc.map_x = (int)gui->cam.posi.x;
	rc.map_y = (int)gui->cam.posi.y;

	// Get the differences in X, Y and Z coordinates between the player and
	// the projectile and normalize them.
	rc.ray_dir.x = (projectile->posi.x - gui->cam.posi.x) * gui->cam.zoom;
	rc.ray_dir.y = (projectile->posi.y - gui->cam.posi.y) * gui->cam.zoom;

	// Calculate the distance to the next intersection point in both X and Y directions
	rc.delta_dist.x = inv_safe(rc.ray_dir.x);
	rc.delta_dist.y = inv_safe(rc.ray_dir.y);

	// Calculate the distance between the player and the projectile
	double	distance = distance_between_player_and_projectile(&gui->cam, projectile, &rc);

	// Exit if projectile not in FOV (horizontally and vertically)
	if (!is_in_fov(&gui->cam, projectile, rc))
	{
		if (projectile_collision(gui, projectile))
		{
			printf("Projectile exploded outside of FOV\n");
			return (clear_projectile(projectile), true);
		}
		else
		{
			printf("Projectile not visible (outside of FOV)\n");
		}
		return (false);
	}



	// PROJECT THE PROJECTILE'S POSITION ON THE PLAYER'S SCREEN HERE
	double	inv_det = 1.0 / (gui->cam.plane.x * rc.ray_dir.y - rc.ray_dir.x * gui->cam.plane.y);
	double	transf_x = inv_det * (gui->cam.dir.y * rc.ray_dir.x - gui->cam.dir.x * rc.ray_dir.y);

	int	screen_x = (SCRWIDTH / 2.0) * (1.0 + transf_x);
	int	screen_y = (SCRHEIGHT / 2.0);

	// horizontal magnitude will always be 1 because projectile->direction is normalized.
	// This is the angle between the map's horizon line and the projectile's path.
	double	vertical_angle_2 = atan2(projectile->direction.z, 1.0);
	printf("vertical_angle_2 = %f\n", vertical_angle_2);

	printf("pitch = %f\n", gui->cam.pitch);


	/*
	// Vertical_angle indicates how much the projectile is pitched upward or downward relative to the player's screen horizontal plane.
	double vertical_angle = atan2(projectile->direction.z, magnitude(rc.ray_dir));
	printf("Vertical angle = %f\n", vertical_angle);

	// Calculate the magnitude of the projectile's motion in the XY plane (horizontal plane)
	double horizontal_magnitude = sqrt(projectile->direction.x * projectile->direction.x +
										projectile->direction.y * projectile->direction.y);

	// Calculate the vertical angle using trigonometry
	double vertical_angle_2 = atan2(projectile->direction.z, horizontal_magnitude);
	printf("Vertical angle relative to horizon = %f\n", vertical_angle_2);

	double max_pitch = 1.5; // Adjust this value as needed
	double max_allowed_vertical_angle = max_pitch / 2.0;

	// Calculate the tangent of the vertical angle
	double tangent = tan(vertical_angle);

	// Convert the tangent to screen coordinates
	int screen_y = (SCRHEIGHT / 2.0) - (SCRHEIGHT * tangent / max_allowed_vertical_angle);
	*/

/*
	double vertical_angle = atan2(projectile->direction.z, magnitude(rc.ray_dir));
	double pitch_correction = vertical_angle - gui->cam.pitch;
	double max_pitch = 1.5; // Adjust this value as needed
	double max_allowed_vertical_angle = max_pitch / 2.0;
	double pitch_correction_ratio = pitch_correction / max_allowed_vertical_angle;

	int screen_x = (SCRWIDTH / 2.0) * (1.0 + transf_x);
	int screen_y = (SCRHEIGHT / 2.0) - (SCRHEIGHT * pitch_correction_ratio);
*/



	if (projectile_collision(gui, projectile))
	{
		printf("Projectile collision detected\n");
		if (cast(gui, &rc, distance))
		{
			draw_projectile_impact(gui, screen_x, screen_y, distance);
			printf("Draw projectile impact\n");
		}
		return (clear_projectile(projectile), true);
	}
	else if (cast(gui, &rc, distance))
	{
		draw_projectile(gui, screen_x, screen_y, distance);
		printf("Draw projectile\n");
	}
	else
	{
		printf("Projectile not visible\n");
	}
	return (false);
}

static void	attack(t_gui *gui, t_prj *projectile)
{
	move_projectile(projectile);
	/*
	printf("prj->posi.x = %f\n", projectile->posi.x);
	printf("prj->posi.y = %f\n", projectile->posi.y);
	printf("prj->posi.z = %f\n", projectile->posi.z);
	printf("prj->dir.x = %f\n", projectile->direction.x);
	printf("prj->dir.y = %f\n", projectile->direction.y);
	printf("prj->dir.z = %f\n", projectile->direction.z);
	printf("----------------\n");
	*/
	(void)raycast_projectile(gui, projectile);
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
	draw_crosshair(gui, 0xE4E6Eb);
	walk_frame = calculate_next_walk_frame(gui, walk_frame);
	set_weapon_position(gui, &weapon_x, &weapon_y, walk_frame);
	if (!projectile.status && (gui->btns & (1 << left_click)))
		initialize_projectile(&gui->cam, &projectile);
	if (projectile.status)
		attack(gui, &projectile);
	imgput(gui->buffer, weapon_x, weapon_y, gui->textures.weapon);
}
