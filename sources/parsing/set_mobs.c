/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 05:11:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/10 20:48:28 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_sprt	*add_mob(t_sprt **list, t_vect posi, t_img **frames)
{
	t_sprt	*sprite;

	sprite = trymalloc(sizeof(t_sprt), 2);
	sprite->posi = posi;
	sprite->stat = HP;
	sprite->amount = -1;
	sprite->solid = 1;
	sprite->type = ALIVE;
	sprite->alpha = 240;
	sprite->fcur = rand() % 8;
	sprite->fnum = 8;
	sprite->frames = frames;
	sprite->dist = 1;
	sprite->next = NULL;
	add_sprite(list, sprite);
	return (sprite);
}

bool	set_mobs(t_gui *gui)
{
	size_t	nb;
	size_t	row;
	size_t	col;

	if (!gui->textures.spframes[SIZE])
		set_frames(gui, &gui->textures.spframes[SIZE], NULL, 8);
	nb = 0;
	row = -1;
	while (++row < gui->map.height)
	{
		col = -1;
		while (++col < gui->map.width)
		{
			if (gui->map.map[row][col] == mob_tile)
			{
				if (!add_mob(&gui->textures.sprites,
					(t_vect){row, col}, gui->textures.spframes[SIZE]))
					return (true);
				if (gui->map.map)
					gui->map.map[row][col] = 0;
			}
		}
	}
	return (false);
}
