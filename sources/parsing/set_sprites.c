/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 02:02:02 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/02 06:55:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	initialize_mob(t_gui *gui, size_t nb)
{
	gui->textures.sprites[nb].posi.y = 0;
	gui->textures.sprites[nb].posi.x = 0;
	gui->textures.sprites[nb].solid = 1;
	gui->textures.sprites[nb].type = STATIONARY;
	gui->textures.sprites[nb].alpha = 0;
	gui->textures.sprites[nb].fcur = rand() % 8;
	gui->textures.sprites[nb].fnum = 8;
	gui->textures.sprites[nb].frames = NULL;
}

static size_t	count_mobs(t_gui *gui)
{
	size_t	nb;
	size_t	row;
	size_t	col;

	if (!gui || !gui->map.map)
		return (0);
	nb = 0;
	row = 0;
	while (row < gui->map.height)
	{
		col = 0;
		while (col < gui->map.width)
		{
			if (gui->map.map[row][col] == 2)
				nb++;
			col++;
		}
		row++;
	}
	return (nb);
}

static bool	set_sporder(t_gui *gui)
{
	size_t	i;

	gui->textures.sporder = malloc(gui->textures.spnb
			* sizeof(gui->textures.sporder));
	if (!gui->textures.sporder)
		return (put_parsing_err("Not enough memory."), true);
	i = 0;
	while (i < (size_t)gui->textures.spnb)
	{
		gui->textures.sporder[i] = i;
		i++;
	}
	return (false);
}

static bool	set_spdist(t_gui *gui)
{
	size_t	i;

	gui->textures.spdist = malloc(gui->textures.spnb
			* sizeof(gui->textures.spdist));
	if (!gui->textures.spdist)
		return (put_parsing_err("Not enough memory."), true);
	i = 0;
	while (i < (size_t)gui->textures.spnb)
		gui->textures.sporder[i++] = 0;
	return (false);
}

bool	set_sprites(t_gui *gui)
{
	int	i;

	gui->textures.spnb = count_mobs(gui);
	gui->textures.sprites = malloc(gui->textures.spnb
			* sizeof(*gui->textures.sprites));
	if (!gui->textures.sprites)
		return (put_parsing_err("Not enough memory."), true);
	i = 0;
	while (i < gui->textures.spnb)
		initialize_mob(gui, i++);
	if (set_sporder(gui))
		return (true);
	if (set_spdist(gui))
		return (true);
	if (set_mobs(gui))
		return (true);
	return (false);
}
