/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 02:02:02 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/23 17:06:58 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_sprt	*add_sprite(t_sprt **list, t_vect posi)
{
	t_sprt	*sprite;
	t_sprt	*tmp;

	sprite = trymalloc(sizeof(t_sprt), 1);
	sprite->posi = posi;
	sprite->solid = 1;
	sprite->type = ALIVE;
	sprite->alpha = 240;
	sprite->fcur = rand() % 8;
	sprite->fnum = 8;
	sprite->frames = NULL;
	sprite->dist = 1;
	sprite->next = NULL;
	if (!*list)
		*list = sprite;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = sprite;
	}
	return (sprite);
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

// static bool	set_sporder(t_gui *gui)
// {
// 	size_t	i;

// 	gui->textures.sporder = malloc(gui->textures.spnb
// 			* sizeof(gui->textures.sporder));
// 	if (!gui->textures.sporder)
// 		return (put_parsing_err("Not enough memory."), true);
// 	i = 0;
// 	while (i < (size_t)gui->textures.spnb)
// 	{
// 		gui->textures.sporder[i] = i;
// 		i++;
// 	}
// 	return (false);
// }

// static bool	set_spdist(t_gui *gui)
// {
// 	size_t	i;

// 	gui->textures.spdist = malloc(gui->textures.spnb
// 			* sizeof(gui->textures.spdist));
// 	if (!gui->textures.spdist)
// 		return (put_parsing_err("Not enough memory."), true);
// 	i = 0;
// 	while (i < (size_t)gui->textures.spnb)
// 		gui->textures.sporder[i++] = 0;
// 	return (false);
// }

bool	set_sprites(t_gui *gui)
{
	// int	i;

	gui->textures.spnb = count_mobs(gui);
	// gui->textures.sprites = trymalloc(1 * sizeof(*gui->textures.sprites), 1);
	// if (!gui->textures.sprites)
	// 	return (put_parsing_err("Not enough memory."), true);
	// i = 0;
	// while (i < gui->textures.spnb)
	// 	add_sprite(gui, i++);
	// if (set_sporder(gui))
	// 	return (true);
	// if (set_spdist(gui))
	// 	return (true);
	if (set_mobs(gui))
		return (true);
	return (false);
}
