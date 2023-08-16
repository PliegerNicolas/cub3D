/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_on_displacement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:57:26 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/16 16:57:51 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	act_on_sprint(t_gui *gui)
{
	static bool	cooldown;

	if (gui->keys & (1 << KP_sprint) && !cooldown)
		gui->cam.sprint_multiplicator = 2;
	else
		gui->cam.sprint_multiplicator = 1;
	if (!nextframe(RATE_SPRINT))
		return ;
	if (gui->cam.sprint_multiplicator == 2)
		gui->cam.stat.get[STA] -= 2 * (gui->cam.stat.get[STA] > 0)
			* (magnitude(gui->cam.speed) > 0);
	else
		gui->cam.stat.get[STA] += (2 - cooldown)
			* (gui->cam.stat.get[STA] < gui->cam.stat.max[STA]);
	if (gui->cam.stat.get[STA] <= 0)
		cooldown = 1;
	if (cooldown && gui->cam.stat.get[STA] == gui->cam.stat.max[STA])
		cooldown = 0;
}

void	act_on_move(t_gui *gui)
{
	t_play	*p;

	p = &gui->cam;
	if (gui->keys & (1 << KP_forth))
		update_speed(&p->speed.x, p->speed_target.x * p->sprint_multiplicator,
			p->accel_rate.x);
	else if (gui->keys & (1 << KP_back))
		update_speed(&p->speed.x, -p->speed_target.x * p->sprint_multiplicator,
			p->accel_rate.x);
	else
		update_speed(&gui->cam.speed.x, 0, gui->cam.accel_rate.x * 1.5);
	if (gui->keys & (1 << KP_right))
		update_speed(&p->speed.y, p->speed_target.y * p->sprint_multiplicator,
			p->accel_rate.y);
	else if (gui->keys & (1 << KP_left))
		update_speed(&p->speed.y, -p->speed_target.y * p->sprint_multiplicator,
			p->accel_rate.y);
	else
		update_speed(&gui->cam.speed.y, 0, gui->cam.accel_rate.y * 1.5);
}
