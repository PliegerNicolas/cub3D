/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/18 15:03:40 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

#define WALK_AMPLITUDE 8
#define WALK_FREQUENCY 30
#define SHOOTING_FREQUENCY 30

static int	calculate_next_frame(t_gui *gui, int frame)
{
	if (gui->cam.speed.x || gui->cam.speed.y)
		return ((frame + 1) % WALK_FREQUENCY);
	else if (frame != 0 && frame != (WALK_FREQUENCY * 0.5))
		return ((frame + 1) % WALK_FREQUENCY);
	return (0);
}

static void	set_weapon_position(t_gui *gui, int *x, int *y, int frame)
{
	int		x_offset;
	int		y_offset;
	float	walk_angle;

	x_offset = gui->textures.weapon->width * 0.2;
	y_offset = gui->textures.weapon->height * 0.2;
	if (gui->cam.speed.x || gui->cam.speed.y || frame)
	{
		walk_angle = (frame / (float)WALK_FREQUENCY * gui->cam.sprint_multiplicator) * 2 * M_PI;
		x_offset += (int)(sin(walk_angle) * WALK_AMPLITUDE);
		y_offset -= (int)(fabs(cos(walk_angle)) * WALK_AMPLITUDE / 2);
	}
	*x = SCRWIDTH - gui->textures.weapon->width + x_offset;
	*y = SCRHEIGHT - gui->textures.weapon->height + y_offset;
}

static void	attack(t_gui *gui, int *frame, int x, int y)
{
	// SKIP
	if (*frame == 0)
		return ;

	printf("shooting = %d, x = %d, y = %d\n", *frame, x, y);
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
	draw_crosshair(gui, 16448250);
	x = 0;
	y = 0;
	frame = calculate_next_frame(gui, frame);
	set_weapon_position(gui, &x, &y, frame);
	if (!shooting && (gui->btns & (1 << left_click)))
		shooting = 1;
	attack(gui, &shooting, x, y);
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
