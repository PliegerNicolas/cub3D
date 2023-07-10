/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/07/15 17:07:12 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

#define FRAMENUMB 20

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
	static t_img	**wpn;
	static int		frame;

	if (!wpn)
		load_texture_arr(gui, &wpn, "textures/wand.xpm", 1);
	if ((gui->btns & (1 << left_click)) && !frame)
		frame = 1;
	if (frame == FRAMENUMB)
		frame = 0;
	if (frame)
		attack(gui, frame++ / (float)FRAMENUMB,
			(t_vect){SCRWIDTH / 2, SCRHEIGHT / 2},
			(t_vect){SCRWIDTH - wpn[0]->width - 1,
			SCRHEIGHT - wpn[0]->height - 1});
	imgput(gui->buffer, SCRWIDTH - wpn[0]->width - (FRAMENUMB - frame),
		SCRHEIGHT - wpn[0]->height - (FRAMENUMB - frame), wpn[0]);
}
