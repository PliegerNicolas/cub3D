/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 02:02:02 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/10 20:34:22 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_sprt	*add_sprite(t_sprt **list, t_sprt *sprite)
{
	t_sprt	*tmp;

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

static char	*get_numbered_texture_path(size_t i, char *path)
{
	char	*temp;
	char	*index;

	index = ft_itoa(i);
	if (!index)
		return (put_parsing_err("Not enough memory."), NULL);
	if (!path)
		path = "textures/solong/slime";
	temp = ft_strjoin(path, index);
	free(index);
	if (!temp)
		return (put_parsing_err("Not enough memory."), NULL);
	path = ft_strjoin(temp, ".xpm");
	free(temp);
	if (!path)
		return (put_parsing_err("Not enough memory."), NULL);
	return (path);
}

bool	set_frames(t_gui *gui, t_img ***frames, char *path, int numbered)
{
	size_t	i;
	char	*numpath;

	if (path && numbered < 0)
		return (load_texture_arr(gui, frames, path, -numbered));
	i = 0;
	while ((int)i < numbered)
	{
		numpath = get_numbered_texture_path(i, path);
		if (!numpath)
			return (put_parsing_err("Not enough memory."), true);
		if (load_texture_arr(gui, frames, numpath, numbered))
			return (free(numpath), true);
		free(numpath);
		i++;
	}
	return (false);
}

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
