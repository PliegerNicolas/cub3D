/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/27 21:16:27 by nicolas          ###   ########.fr       */
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

/*
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
	int y = (int)(SCRHEIGHT / 2) + (int)(SCRHEIGHT * (player->posi.z) / transform_y);

	if (projectile_collision(gui, projectile))
	{
		draw_projectile_impact(gui, x, y, distance);
		clear_projectile(projectile);
	}
	else
		draw_projectile(gui, x, y, distance);

	return (false);
}
*/

/*
static void	display_projectile(t_gui *gui, t_prj *projectile)
{
	(void)gui;
	(void)projectile;
}

static bool is_projectile_visible(t_gui *gui, t_vect player_position, t_vect projectile_position)
{
    // Get the differences in X and Y coordinates between the player and the projectile
    double ray_dir_x = projectile_position.x - player_position.x;
    double ray_dir_y = projectile_position.y - player_position.y;

    // Calculate the distance between the player and the projectile
    double distance = sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y);

    // Normalize the ray direction vector
    double step_x = ray_dir_x / distance;
    double step_y = ray_dir_y / distance;

    // Determine the initial position of the ray based on the player's position and the direction of the ray
    double	current_x, current_y;
    if (step_x > 0)
	{
        current_x = ceil(player_position.x); // Increment X for east direction
	}
    else
	{
        current_x = floor(player_position.x);  // Decrement X for west direction
	}
    if (step_y > 0)
	{
        current_y = ceil(player_position.y); // Increment Y for south direction
	}
    else
	{
        current_y = floor(player_position.y);  // Decrement Y for north direction
	}

    // Calculate the distance to the next intersection point in both X and Y directions
    double delta_x = fabs((current_x - player_position.x + (step_x > 0 ? 1.0 : 0.0)) / ray_dir_x);
    double delta_y = fabs((current_y - player_position.y + (step_y > 0 ? 1.0 : 0.0)) / ray_dir_y);

    // Perform the DDA algorithm along the entire line between the player and the projectile
    while (distance > 0)
    {
        // Check if the current cell contains a solid wall (assuming wall tiles have ID > 0)
        int cell_x = (int)current_x;
        int cell_y = (int)current_y;
        if (gui->map.map[cell_x][cell_y] % DOOR_OPEN != floor_tile
			|| projectile_position.z <= -1.0 || projectile_position.z >= 1.0)
		{
			printf("Wall or ceiling or floor found\n");
            return false; // The projectile is obstructed by a wall
		}

        if (delta_x < delta_y)
        {
            delta_x += fabs(step_x);
            current_x += step_x; // Adjust current_x based on ray direction
        }
        else
        {
            delta_y += fabs(step_y);
            current_y += step_y; // Adjust current_y based on ray direction
        }

        // Update the remaining distance
        distance -= 1.0;
    }

	printf("Projectile found\n");
    // If the loop finishes without hitting a wall, the projectile is visible
    return (true);
}
*/

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

	// ???
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

	//casting mecanism
	if (cast(gui, &rc, distance))
	{
		printf("Draw projectile\n");
	}

	//temp
	if (projectile->posi.x < 0 || projectile->posi.x > gui->map.width
		|| projectile->posi.y < 0 || projectile->posi.y > gui->map.height)
	{
		printf("Projectile outside of map\n");
		return (true);
	}
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
