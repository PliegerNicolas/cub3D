/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/08/16 17:27:43 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static double	calc_distance(t_vect from, t_vect to)
{
	double	distance;
	double	dx;
	double	dy;

	dx = to.x - from.x;
	dy = to.y - from.y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance);
}

static double	vertical_matrix_transf(t_gui *gui, t_rc *rc)
{
	double	inv_det;
	double	transf_x;

	inv_det = 1.0 / (gui->cam.plane.x * rc->ray_dir.y
			- rc->ray_dir.x * gui->cam.plane.y);
	transf_x = inv_det * (gui->cam.dir.y * rc->ray_dir.x
			- gui->cam.dir.x * rc->ray_dir.y) * gui->cam.zoom;
	return (transf_x);
}

static bool	raycast_projectile(t_gui *gui, t_prj *projectile)
{
	t_rc	rc;
	int		screen_x;
	int		screen_y;
	bool	target_hit;
	double	distance;

	target_hit = !move_projectile(gui, projectile);
	rc.ray_dir.x = (projectile->posi.x - gui->cam.posi.x) * gui->cam.zoom;
	rc.ray_dir.y = (projectile->posi.y - gui->cam.posi.y) * gui->cam.zoom;
	screen_x = (SCRWIDTH / 2.0) * (1.0 + vertical_matrix_transf(gui, &rc));
	screen_y = (SCRHEIGHT / 2.0) + (gui->cam.pitch * SCRHEIGHT);
	if (is_projectile_obstructed(gui, projectile))
	{
		if (!target_hit)
			return (false);
	}
	else
	{
		distance = calc_distance(gui->cam.posi, projectile->posi);
		if (target_hit)
			draw_projectile_impact(gui, screen_x, screen_y, distance);
		else
			return (draw_projectile(gui, screen_x, screen_y, distance), false);
	}
	return (true);
}

static void	attack(t_gui *gui)
{
	static t_prj	projectiles[MAX_PROJECTILES];
	size_t			i;

	i = 0;
	if (((gui->btns & (1 << left_click))
			|| gui->keys & (1 << KP_space))
		&& nextframe(RATE_SHOOT))
	{
		i = 0;
		while (i < MAX_PROJECTILES && projectiles[i].status)
			i++;
		if (i < MAX_PROJECTILES)
		{
			initialize_projectile(&gui->cam, &projectiles[i]);
			gui->cam.stat.get[AMMO]--;
		}
	}
	i = 0;
	while (i < MAX_PROJECTILES)
	{
		if (projectiles[i].status && raycast_projectile(gui, &projectiles[i]))
			clear_projectile(&projectiles[i]);
		i++;
	}
}

void	weapon(t_gui *gui)
{
	static int		walk_frame;
	int				weapon_x;
	int				weapon_y;

	if (!gui->textures.weapon)
		return ;
	weapon_x = 0;
	weapon_y = 0;
	walk_frame = calculate_next_walk_frame(gui, walk_frame);
	set_weapon_position(gui, &weapon_x, &weapon_y, walk_frame);
	draw_crosshair(gui, 0xFFFFFF);
	if (gui->cam.stat.get[AMMO] >= 1)
		attack(gui);
	imgput(gui->buffer, weapon_x, weapon_y, gui->textures.weapon);
}
