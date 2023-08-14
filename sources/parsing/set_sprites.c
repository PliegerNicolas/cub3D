/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 02:02:02 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/14 15:22:07 by nplieger         ###   ########.fr       */
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

bool	set_sprites(t_gui *gui)
{
	gui->textures.spnb = count_mobs(gui);
	if (set_mobs(gui))
		return (true);
	return (false);
}
