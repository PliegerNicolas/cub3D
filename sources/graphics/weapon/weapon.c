/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/19 13:45:03 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	draw_projectile(t_play *p, t_vect projectile, int color)
{
	(void)p;
	(void)projectile;
	(void)color;
}

static int	check_contact(t_gui *gui, t_vect projectile)
{
	t_vect	sprite_pos;
	int		i;

	if (gui->map.map[(int)projectile.x][(int)projectile.y] % DOOR_OPEN != floor_tile)
		return (1);
	i = 0;
	printf("projectile.x = %f, projectile.y = %f\n", projectile.x, projectile.y);
	while (i < gui->textures.spnb)
	{
		sprite_pos = gui->textures.sprites->posi;
		// height not considered. 0.25 is virtual hitbox of sprite
		printf("sprite.x = %f, sprite.y = %f\n", sprite_pos.x, sprite_pos.y);
		if (projectile.x < sprite_pos.x - 0.5 && projectile.x > sprite_pos.x + 0.5)
		{
			printf("x ok\n");
			if (projectile.y < sprite_pos.y - 0.5 && projectile.y > sprite_pos.y + 0.5)
				return (1);
		}
		i++;
	}
	printf("\n");
	return (0);
}

static void	attack(t_gui *gui, int *frame)
{
	static t_vect	projectile;
	static t_vect	direction;
	double			projectile_speed;

	// INITIALIZE
	if (*frame == 1)
	{
		projectile.x = gui->cam.posi.x;
		projectile.y = gui->cam.posi.y;
		projectile.z = 0.66;
		direction.x = gui->cam.dir.x;
		direction.y = gui->cam.dir.y;
		direction.z = gui->cam.posi.z;
	}
	// ACT

	projectile_speed = 0.25;
	projectile.x += direction.x * projectile_speed;
	projectile.y += direction.y * projectile_speed;
	projectile.z += direction.z * projectile_speed;
	if (check_contact(gui, projectile))
	{
		printf("Contact !\n");
		*frame = 0;
		return ;
	}
	//printf("facing ... %f, %f, %f\n", direction.x, direction.y, direction.z);
	draw_projectile(&gui->cam, projectile, 0xE4E6EB);

	// END
	if (*frame >= SHOOTING_FREQUENCY)
		*frame = 0;
	else
		(*frame)++;
}

void	weapon(t_gui *gui)
{
	static int	frame;
	static int	shooting;
	int			x;
	int			y;

	if (!gui->textures.weapon)
		return ;
	draw_crosshair(gui, 0xE4E6EB);
	x = 0;
	y = 0;
	frame = calculate_next_walk_frame(gui, frame);
	set_weapon_position(gui, &x, &y, frame);
	if (!shooting && (gui->btns & (1 << left_click)))
		shooting = 1;
	if (shooting)
		attack(gui, &shooting);
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
