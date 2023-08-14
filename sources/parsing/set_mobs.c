/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 05:11:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/14 16:41:10 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_sprt	*add_mob(t_gui *gui, t_vect posi, size_t which)
{
	t_sprt	*sprite;

	sprite = trymalloc(sizeof(t_sprt), 2);
	sprite->posi = posi;
	sprite->stat = HP;
	sprite->amount = -1;
	sprite->solid = 1;
	sprite->type = ALIVE;
	sprite->alpha = 240;
	sprite->fnum = gui->textures.spfrsizes[which];
	sprite->fcur = rand() % sprite->fnum;
	sprite->frames = gui->textures.spframes[which];
	sprite->scale = (t_vect){1, 1};
	sprite->offset = 0;
	sprite->dist = 1;
	sprite->next = NULL;
	add_sprite(&gui->textures.sprites, sprite);
	gui->textures.spnb++;
	return (sprite);
}

t_sprt	*add_pack(t_gui *gui, t_vect posi, size_t which)
{
	t_sprt	*sprite;

	sprite = trymalloc(sizeof(t_sprt), 2);
	sprite->posi = posi;
	sprite->stat = which;
	sprite->amount = 50 / (which + 1);
	sprite->solid = 1;
	sprite->type = COLLECTIBLE;
	sprite->alpha = 0;
	sprite->fnum = gui->textures.spfrsizes[which];
	sprite->fcur = rand() % sprite->fnum;
	sprite->frames = gui->textures.spframes[which];
	sprite->scale = (t_vect){2.5, 2.5};
	sprite->offset = sprite->frames[0]->height * 6;
	sprite->dist = 1;
	sprite->next = NULL;
	add_sprite(&gui->textures.sprites, sprite);
	gui->textures.spnb++;
	return (sprite);
}

t_sprt	*add_obj(t_gui *gui, t_vect posi, size_t which)
{
	t_sprt	*sprite;

	sprite = trymalloc(sizeof(t_sprt), 2);
	sprite->posi = posi;
	sprite->stat = which;
	sprite->amount = 0;
	sprite->solid = 0;
	sprite->type = STATIONARY;
	sprite->alpha = 0;
	sprite->fnum = gui->textures.spfrsizes[which];
	sprite->fcur = rand() % sprite->fnum;
	sprite->frames = gui->textures.spframes[which];
	sprite->scale = (t_vect){2.5, 2.5};
	sprite->offset = sprite->frames[0]->height * 6;
	sprite->dist = 1;
	sprite->next = NULL;
	add_sprite(&gui->textures.sprites, sprite);
	gui->textures.spnb++;
	return (sprite);
}

bool	set_mobs(t_gui *gui)
{
	size_t	row;
	size_t	col;

	if (!gui->textures.spframes[SIZE + NB_OBJTYPE])
		set_frames(gui, SIZE + NB_OBJTYPE, NULL, 8);
	nb = 0;
	row = -1;
	while (++row < gui->map.height)
	{
		col = -1;
		while (++col < gui->map.width)
		{
			if (gui->map.map[row][col] == mob_tile)
			{
				if (!add_mob(gui, (t_vect){row, col}, SIZE + NB_OBJTYPE))
					return (true);
				if (gui->map.map)
					gui->map.map[row][col] = 0;
			}
			if (gui->map.map[row][col] == pack_tile)
			{
				if (!add_pack(gui, (t_vect){row, col}, HP))
					return (true);
				if (gui->map.map)
					gui->map.map[row][col] = 0;
			}
			if (gui->map.map[row][col] == obj_tile)
			{
				if (!add_obj(gui, (t_vect){row, col}, SIZE))
					return (true);
				if (gui->map.map)
					gui->map.map[row][col] = 0;
			}
		}
	}
	return (false);
}
