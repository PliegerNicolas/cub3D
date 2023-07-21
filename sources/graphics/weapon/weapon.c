/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/21 05:53:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	move_projectile(t_play *player, t_vect *projectile,
	t_vect *direction, int *projectile_life_cycle)
{
	if (*projectile_life_cycle <= 1)
	{
		projectile->x = player->posi.x;
		projectile->y = player->posi.y;
		projectile->z = 0.66;
		direction->x = player->dir.x;
		direction->y = player->dir.y;
		direction->z = player->posi.z;
	}
	else
	{
		projectile->x += direction->x * (double)PROJECTILE_SPEED;
		// slow down relatif to pitch
		projectile->y += direction->y * (double)PROJECTILE_SPEED;
		// slow down relative to pitch
		projectile->z += direction->z * (double)PROJECTILE_SPEED;
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
		|| (proj->z <= 0 || proj->z >= 1))
		return (1);
	i = 0;
	while (i < (size_t)gui->textures.spnb)
	{
		sprite = &gui->textures.sprites[i];
		if (proj->z > 0 && proj->z < 0.75)
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

static void	draw_projectile(t_gui *gui, t_vect *projectile)
{
	t_play	*player;

	player = &gui->cam;

    // Calculate ray from player to projectile
    double projRayDirX = projectile->x - player->posi.x;
    double projRayDirY = projectile->y - player->posi.y;
    double projDist = sqrt(projRayDirX * projRayDirX + projRayDirY * projRayDirY);
    projRayDirX /= projDist;
    projRayDirY /= projDist;

	double dotProduct = player->dir.x * projRayDirX + player->dir.y * projRayDirY;
	printf("fov = %f\n", player->fov);
	if (dotProduct > cos(player->fov / 2))
	{
		printf("INSIDE fov\n");
	}
	else
	{
		printf("OUTSIDE fov\n");
	}

	(void)player;
	(void)gui;
	(void)projectile;
	pixput(gui->buffer, SCRWIDTH / 2, SCRHEIGHT / 2 + 10, 0xFFC0CB);
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

/*

static void	projectile(t_img *img, t_vect p, int size, int color)
{
	int	x;
	int	y;

	y = p.y - size;
	while (++y < p.y + size)
	{
		x = p.x - size;
		while (++x < p.x + size)
			pixput(img, x, y, color);
	}
}

static void	attack(t_gui *gui, float frame, t_vect target, t_vect origin)
{
	t_vect	where;
	t_vect	towards;
	t_sprt	*sprite;
	int		iter;

	where.x = frame * target.x + (1 - frame) * origin.x;
	where.y = frame * target.y + (1 - frame) * origin.y;
	projectile(gui->buffer, where, 20 * (1 - frame), 0xCAFEBEBE);
	iter = -1;
	while (frame >= 0.93 && ++iter < gui->textures.spnb)
	{
		sprite = &gui->textures.sprites[iter];
		towards = delta(gui->cam.posi, sprite->posi);
		if (angle(gui->cam.dir, towards) < 0.1)
			sprite->type = (sprite->type + 1) % (DEAD + 1);
		printf("vomidupipi %d %f\n", sprite->type, angle(gui->cam.dir, towards));
	}
}

void	weapon(t_gui *gui)
{
	(void)gui;
	static int		frame;

	if (!gui->textures.weapon)
		return ;
	if ((gui->btns & (1 << left_click)) && !frame)
		frame = 1;
	if (frame == FRAMENUMB)
		frame = 0;
	if (frame)
		attack(gui, frame++ / (float)FRAMENUMB,
			(t_vect){SCRWIDTH / 2, SCRHEIGHT / 2},
			(t_vect){SCRWIDTH - gui->textures.weapon[0].width - 1,
			SCRHEIGHT - gui->textures.weapon[0].height - 1});
	imgput(gui->buffer, SCRWIDTH - gui->textures.weapon[0].width - (FRAMENUMB - frame),
		SCRHEIGHT - gui->textures.weapon[0].height - (FRAMENUMB - frame), gui->textures.weapon);
}
*/
