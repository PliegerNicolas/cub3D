/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:28:25 by emis              #+#    #+#             */
/*   Updated: 2023/08/16 20:46:07 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	gain_xp(t_gui *gui, t_sprt *ded)
{
	gui->cam.stat.get[XP] += abs(ded->amount) * 15;
	while (gui->cam.stat.get[XP] >= gui->cam.stat.max[XP])
	{
		gui->cam.stat.get[XP] -= gui->cam.stat.max[XP];
		gui->cam.stat.get[LVL]++;
		gui->cam.stat.max[HP] += 2 * (1 + gui->cam.stat.get[LVL] / 5);
		gui->cam.stat.max[ARM] += 2 * (1 + gui->cam.stat.get[LVL] / 5);
		gui->cam.stat.max[STA] += sqrt(gui->cam.stat.get[LVL]);
		gui->cam.stat.max[XP] += 5 * (1 + gui->cam.stat.get[LVL] / 5);
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
			-1, gui->cam.stat.max[fld]);
}
