/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_weapon_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:55:29 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/17 23:19:25 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

t_img	**get_weapon_textures(t_gui *gui)
{
	t_img		**weapon_texture;
	int			which;

	which = SIZE + NB_OBJTYPE + NB_MOBTYPE + gui->cam.selected_weapon;
	weapon_texture = gui->textures.spframes[which];
	if (!weapon_texture)
		return (NULL);
	return (weapon_texture);
}

void	next_weapon_frame(t_gui *gui, size_t *weapon_frame)
{
	int	which;

	if (!(*weapon_frame))
		return ;
	which = SIZE + NB_OBJTYPE + NB_MOBTYPE + gui->cam.selected_weapon;
	if ((*weapon_frame + 1) < gui->textures.spfrsizes[which])
	{
		if (nextframe(RATE_WEAPON))
			(*weapon_frame)++;
	}
	else
		(*weapon_frame) = 0;
}
