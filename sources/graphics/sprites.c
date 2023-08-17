/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:26:42 by emis              #+#    #+#             */
/*   Updated: 2023/08/17 23:23:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	sort_lst(t_sprt **lst, t_sprt *old)
{
	t_sprt	*sp;

	sp = *lst;
	while (sp->next)
	{
		if (sp->dist < sp->next->dist)
		{
			if (sp == *lst)
			{
				*lst = (*lst)->next;
				sp->next = (*lst)->next;
				(*lst)->next = sp;
			}
			else
			{
				old->next = sp->next;
				sp->next = old->next->next;
				old->next->next = sp;
			}
			sp = *lst;
		}
		old = sp;
		sp = sp->next;
	}
}

void	set_dist_and_sort(t_tex *tex, t_vect *from)
{
	t_sprt	*sp;
	double	last;
	bool	sort;

	sp = tex->sprites;
	last = -1;
	sort = 0;
	while (sp)
	{
		sp->dist = ((from->x - sp->posi.x)
				* (from->x - sp->posi.x)
				+ (from->y - sp->posi.y)
				* (from->y - sp->posi.y));
		if (last > -1 && sp->dist > last)
			sort = 1;
		last = sp->dist;
		sp = sp->next;
	}
	if (sort)
		sort_lst(&tex->sprites, tex->sprites);
}

static bool	shift_type(t_gui *gui, t_sprt *sp, t_sprt *old)
{
	if (sp->type == COLLECTIBLE)
		sp->offset = (sp->offset + (int)sp->offset % 40)
			- ((int)sp->offset + 4) % 40;
	if (sp->type != DEAD)
		sp->fcur = (sp->fcur + 1) % sp->fnum;
	else if (sp->type == DEAD && sp->alpha < 0)
	{
		if (sp == gui->textures.sprites)
			gui->textures.sprites = sp->next;
		else
			old->next = sp->next;
		if (sp->amount < 0)
		{
			gain_xp(gui, sp);
			if (rand() % XP == 0)
				add_pack(gui, sp->posi, rand() % XP);
		}
		garbaj(sp, NULL, -1);
		--gui->textures.spnb;
		return (true);
	}
	return (false);
}

void	frame_shift(t_gui *gui)
{
	t_sprt	*sp;
	t_sprt	*old;

	if (!nextframe(RATE_MOB))
		return ;
	sp = gui->textures.sprites;
	old = sp;
	while (sp)
	{
		if (shift_type(gui, sp, old))
			sp = gui->textures.sprites;
		old = sp;
		if (sp)
			sp = sp->next;
	}
}

void	update_sprite(t_gui *gui, t_sprt *cur)
{
	if (cur->type == DEAD)
		return ((void)(cur->alpha -= 5 * (cur->alpha >= 0),
			cur->scale = scale(cur->scale, 1.1),
			cur->offset += 20));
	if (cur->dist > .2)
	{
		if (cur->type == ALIVE)
			check_and_move(gui->map, &cur->posi, delta(cur->posi,
					gui->cam.posi), 0.025 + ((rand() % 10) / 1000.0));
	}
	else
		touch_sprite(gui, cur);
}
