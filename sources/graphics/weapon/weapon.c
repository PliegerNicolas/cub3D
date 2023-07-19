/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/19 11:14:35 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	attack(t_gui *gui, int *frame)
{
	static t_3dvect	projectile;
	static t_3dvect	direction;

	// INITIALIZE
	if (*frame == 1)
	{
		projectile.x = gui->cam.posi.x;
		projectile.y = gui->cam.posi.y;
		projectile.z = 0.66;
		direction.x = gui->cam.dir.x;
		direction.y = gui->cam.dir.y;
		direction.z = (gui->cam.pitch * 100) / SCRHEIGHT;
	}
	// ACT

	projectile.x += direction.x * 1;
	projectile.y += direction.y * 1;
	projectile.z += direction.z * 1;
	printf("pitch ... %d\n", gui->cam.pitch);
	printf("facing ... %f, %f, %f\n", direction.x, direction.y, direction.z);
	(void)projectile;
	(void)direction;
	(void)gui;

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
