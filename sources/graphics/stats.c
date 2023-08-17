/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:28:25 by emis              #+#    #+#             */
/*   Updated: 2023/08/17 23:16:09 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	gain_xp(t_gui *gui, t_sprt *ded)
{
	gui->cam.stat.get[XP] += abs(ded->amount)
		* (15 - 14 * (ded->type != DEAD));
	while (gui->cam.stat.get[XP] >= gui->cam.stat.max[XP])
	{
		gui->cam.stat.get[XP] -= gui->cam.stat.max[XP];
		gui->cam.stat.get[LVL]++;
		gui->cam.stat.max[HP] += 5 * (1 + gui->cam.stat.get[LVL] / 5);
		gui->cam.stat.max[ARM] += 5 * (1 + gui->cam.stat.get[LVL] / 5);
		gui->cam.stat.max[STA] += sqrt(gui->cam.stat.get[LVL]);
		gui->cam.stat.get[STA] = gui->cam.stat.max[STA];
		gui->cam.stat.max[XP] += 10 * (1 + gui->cam.stat.get[LVL] / 5);
	}
}

void	regen(t_gui *gui, t_fld fld, int amount, enum e_rates rate)
{
	if (gui->cam.stat.get[fld] >= gui->cam.stat.max[fld]
		|| !nextframe(rate))
		return ;
	if (gui->cam.stat.get[fld] < -1)
		printf("Weird stuff happening to stat %d\n", fld);
	gui->cam.stat.get[fld] = bind(gui->cam.stat.get[fld] + amount,
			-1, gui->cam.stat.max[fld] + 1);
}

void	touch_sprite(t_gui *gui, t_sprt *sprt)
{
	if (sprt->stat == HP && sprt->amount < 0
		&& gui->cam.stat.get[ARM] > 0)
		gui->cam.stat.get[ARM] = bind(gui->cam.stat.get[ARM] + sprt->amount
				* !(rand() % 4), 0, gui->cam.stat.max[ARM]);
	else if (gui->cam.stat.get[sprt->stat] == gui->cam.stat.max[sprt->stat]
		&& sprt->amount > 0)
		gain_xp(gui, sprt);
	else if (gui->cam.stat.get[sprt->stat] > -1)
		gui->cam.stat.get[sprt->stat] = bind(
				gui->cam.stat.get[sprt->stat] + sprt->amount, 0,
				gui->cam.stat.max[sprt->stat] + 1);
	if (sprt->type == COLLECTIBLE)
	{
		sprt->alpha = -1;
		sprt->type = DEAD;
	}
}
