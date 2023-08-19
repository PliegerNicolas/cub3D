/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_on_toggle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:58:26 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/19 12:41:07 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	act_on_interaction(t_gui *gui)
{
	if (check_press((gui->keys & (1 << KP_interact)) != 0, 0))
		interact(gui);
}

static void	act_on_map(t_gui *gui)
{
	if (check_press((gui->keys & (1 << KP_map)) != 0, 1))
	{
		select_map_type(&gui->cam.rndr);
		gui->rendered = 0;
	}
}

static void	act_on_statistics(t_gui *gui)
{
	if (check_press((gui->keys & (1 << KP_statistics)) != 0, 2))
	{
		toggle_mask(&gui->cam.rndr, STATISTICS, TOGGLE);
		gui->rendered = 0;
	}
}

static void	act_on_weapon_swap(t_gui *gui)
{
	if (check_press((gui->keys & (1 << KP_swap_weapon)) != 0, 3))
	{
		gui->cam.selected_weapon++;
		gui->cam.selected_weapon %= NB_WPNTYPE;
		if (!gui->textures.spframes[SIZE + NB_OBJTYPE
				+ NB_MOBTYPE + gui->cam.selected_weapon])
			gui->cam.selected_weapon = 0;
		gui->rendered = 0;
	}
}

void	act_on_toggles(t_gui *gui)
{
	if (!BONUS)
		return ;
	act_on_interaction(gui);
	act_on_map(gui);
	act_on_statistics(gui);
	act_on_weapon_swap(gui);
}
