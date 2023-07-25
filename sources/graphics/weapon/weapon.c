/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/25 10:15:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	move_projectile(t_play *player, t_vect *projectile,
	t_vect *direction, int *projectile_life_cycle)
{
	if (*projectile_life_cycle <= 1)
	{
		// Add offset so it starts from the weapon
		projectile->x = player->posi.x;
		projectile->y = player->posi.y;
		projectile->z = player->posi.z;
		direction->x = player->dir.x;
		direction->y = player->dir.y;
		direction->z = player->posi.z;
	}
	else
	{
        // Calculate pitch angle in radians
        double pitch_rad = direction->z / 1.5 * (M_PI / 180.0);
        
        // Calculate speed multipliers for x, y, and z directions
        double speed_multiplier_x = cos(pitch_rad);
        double speed_multiplier_y = cos(pitch_rad);
        double speed_multiplier_z = sin(pitch_rad); // Accelerate more upwards
        
        // Apply the speed multipliers to the projectile's velocity
        projectile->x += direction->x * (double)PROJECTILE_SPEED * speed_multiplier_x;
        projectile->y += direction->y * (double)PROJECTILE_SPEED * speed_multiplier_y;
        projectile->z += direction->z * (double)PROJECTILE_SPEED * speed_multiplier_z;
	}
}

static void	end_projectile(t_vect *projectile, t_vect *direction,
	int *projectile_life_cycle)
{
	if (*projectile_life_cycle < MAX_PROJECTILE_LIFE_CYCLE)
		(*projectile_life_cycle)++;
	else
	{
		*projectile_life_cycle = 0;
		projectile->x = 0;
		projectile->y = 0;
		projectile->z = 0;
		direction->x = 0;
		direction->y = 0;
		direction->z = 0;
	}
}

static bool	projectile_hit(t_gui *gui, t_vect *proj)
{
	size_t	i;
	t_sprt	*sprite;

	if (gui->map.map[(int)proj->x][(int)proj->y] % DOOR_OPEN != floor_tile
		|| (proj->z <= -1.0 || proj->z >= 1.0))
		return (1);
	i = 0;
	while (i < (size_t)gui->textures.spnb)
	{
		sprite = &gui->textures.sprites[i];
		//printf("proj->z = %f\n", proj->z);
		if (proj->z > -0.2 && proj->z < 0.0)
		{
			if (sprite->posi.x - 0.25 < proj->x && sprite->posi.x + 0.25 > proj->x)
			{
				if (sprite->posi.y - 0.25 < proj->y && sprite->posi.y + 0.25 > proj->y)
				{
					sprite->type = DEAD;
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

static void draw_projectile(t_gui *gui, t_vect *projectile)
{
    t_play *player = &gui->cam;
    double projRayDirX = projectile->x - player->posi.x;
    double projRayDirY = projectile->y - player->posi.y;

    // Check if the projectile is within the player's field of view
    double dotProduct = player->dir.x * projRayDirX
		+ player->dir.y * projRayDirY;
    if (dotProduct > cos(player->fov / 2))
    {
        // The projectile is within the FOV, render it

        // Convert world position of projectile to screen coordinates
        double invDet = 1.0 / (player->plane.x * player->dir.y
			- player->dir.x * player->plane.y);
        double transformX = invDet * (player->dir.y * (projectile->x
			- player->posi.x) - player->dir.x * (projectile->y - player->posi.y));
        double transformY = invDet * (-player->plane.y
			* (projectile->x - player->posi.x) + player->plane.x
			* (projectile->y - player->posi.y));

        int spriteScreenX = (int)((SCRWIDTH / 2)
			* (1 + transformX / transformY));
		int	spriteScreenY = (int)(SCRHEIGHT / 2)
			+ (SCRHEIGHT * player->posi.z) - (SCRHEIGHT * projectile->z);

        // Check if the projectile is within the screen boundaries before rendering
        if (spriteScreenX >= 0 && spriteScreenX < SCRWIDTH
			&& spriteScreenY >= 0 && spriteScreenY < SCRHEIGHT)
            pixput(gui->buffer, spriteScreenX, spriteScreenY, 0xf59acf);
    }
}

static void	attack(t_gui *gui, int *projectile_life_cycle)
{
	static t_vect	projectile;
	static t_vect	direction;

	move_projectile(&gui->cam, &projectile, &direction, projectile_life_cycle);
	if (projectile_hit(gui, &projectile))
		*projectile_life_cycle = MAX_PROJECTILE_LIFE_CYCLE;
	draw_projectile(gui, &projectile);
	end_projectile(&projectile, &direction, projectile_life_cycle);
}

void	weapon(t_gui *gui)
{
	static int	frame;
	static int	projectile_life_cycle;
	int			x;
	int			y;

	if (!gui->textures.weapon)
		return ;
	draw_crosshair(gui, 0xE4E6EB);
	x = 0;
	y = 0;
	frame = calculate_next_walk_frame(gui, frame);
	set_weapon_position(gui, &x, &y, frame);
	if (!projectile_life_cycle && (gui->btns & (1 << left_click)))
		projectile_life_cycle = 1;
	if (projectile_life_cycle)
		attack(gui, &projectile_life_cycle);
	imgput(gui->buffer, x, y, gui->textures.weapon);
}
