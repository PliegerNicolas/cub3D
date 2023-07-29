/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/29 14:15:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	move_projectile(t_prj *projectile)
{
	projectile->posi.x += (double)PROJECTILE_SPEED
			* projectile->direction.x;
	projectile->posi.y += (double)PROJECTILE_SPEED
			* projectile->direction.y;
	projectile->posi.z += (double)PROJECTILE_SPEED
			* (projectile->direction.z / 1.5);
}

static void world_to_screen(const t_gui *gui, const t_prj *projectile, int *x, int *y)
{
    t_vect delta;
    double inv_det;
    double trans_x, trans_y;

    // Calculate the difference between the player's position and the projectile's position
    delta.x = projectile->posi.x - gui->cam.posi.x;
    delta.y = projectile->posi.y - gui->cam.posi.y;

    // Calculate the inverse of the determinant to transform the coordinates
    inv_det = 1.0 / (gui->cam.plane.x * gui->cam.dir.y - gui->cam.dir.x * gui->cam.plane.y);

    // Transform the x and y coordinates using the inverse determinant
    trans_x = inv_det * (gui->cam.dir.y * delta.x - gui->cam.dir.x * delta.y);
    trans_y = inv_det * (-gui->cam.plane.y * delta.x + gui->cam.plane.x * delta.y);

    // The screen coordinates of the projectile's pixel
    *x = (int)((SCRWIDTH / 2) * (1 + trans_x / trans_y));
    *y = (int)(SCRHEIGHT / 2 - SCRHEIGHT / trans_y);
}

static void adjust_for_pitch_orientation(t_gui *gui, int *x, int *y)
{
    double pitch_rad = (gui->cam.posi.z / 1.5) * M_PI; // Convert pitch from [-1.5, 1.5] to radians

    // Vertical Adjustment based on Pitch (gui->cam.posi.z)
    double vertical_adjust = (SCRHEIGHT / 2) * tan(pitch_rad);

    // Horizontal Adjustment based on Orientation (gui->cam.dir.x, gui->cam.dir.y)
    double angle = atan2(gui->cam.dir.y, gui->cam.dir.x);
    double horizontal_adjust = (*y - SCRHEIGHT / 2) * tan(angle);

    // Apply the adjustments to the screen coordinates
    *x = (*x + (int)horizontal_adjust);
    *y = *y + (int)vertical_adjust;
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
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}

        // Update the remaining distance
        distance -= 1.0;
	}
	return (true);
}


static bool raycast_projectile(t_gui *gui, t_prj *projectile)
{
	t_rc	rc;

    // Get the differences in X and Y coordinates between the player and the projectile
	rc.ray_dir.x = (projectile->posi.x - gui->cam.posi.x) * gui->cam.zoom;
	rc.ray_dir.y = (projectile->posi.y - gui->cam.posi.y) * gui->cam.zoom;

	// Get the player's coordinates relative to the grid (convert to int and round down)
	rc.map_x = (int)gui->cam.posi.x;
	rc.map_y = (int)gui->cam.posi.y;

    // Calculate the distance to the next intersection point in both X and Y directions
	rc.delta_dist.x = inv_safe(rc.ray_dir.x);
	rc.delta_dist.y = inv_safe(rc.ray_dir.y);
	
	// Calculate the distance between the player and the projectile
    double distance = sqrt(rc.ray_dir.x * rc.ray_dir.x + rc.ray_dir.y * rc.ray_dir.y);

	int x, y = 0;
	world_to_screen(gui, projectile, &x, &y);
	adjust_for_pitch_orientation(gui, &x, &y);

	//casting mecanism
	if (cast(gui, &rc, distance))
	{
		if (projectile_collision(gui, projectile))
		{
			//printf("Draw projectile impact\n");
			draw_projectile_impact(gui, x, y, distance);
			clear_projectile(projectile);
			return (true);
		}
		//printf("Draw projectile\n");
		draw_projectile(gui, x, y, distance);
		return (false);
		//draw_projectile(gui, projectile);
	}

	if (projectile_collision(gui, projectile))
	{
		clear_projectile(projectile);
		printf("Projectile not visible exploded\n");
		return (true);
	}

	printf("Projectile not visible\n");
	return (false);
}

static void	attack(t_gui *gui, t_prj *projectile)
{
	move_projectile(projectile);
	if (raycast_projectile(gui, projectile))
		clear_projectile(projectile);
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
