/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 02:02:02 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/14 16:25:55 by emis             ###   ########.fr       */
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

// static size_t	count_mobs(t_gui *gui)
// {
// 	size_t	nb;
// 	size_t	row;
// 	size_t	col;

// 	if (!gui || !gui->map.map)
// 		return (0);
// 	nb = 0;
// 	row = 0;
// 	while (row < gui->map.height)
// 	{
// 		col = 0;
// 		while (col < gui->map.width)
// 		{
// 			if (gui->map.map[row][col] == 2)
// 				nb++;
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (nb);
// }

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

bool	set_mob_obj_frames(t_gui *gui, size_t which, char **args, int num)
{
	int	iter;
	int	tmp;

	iter = 2;
	tmp = ft_atoi(args[iter]);
	if (args[iter + 1])
		iter++;
	if ((which == 6 && iter >= NB_OBJTYPE)
		|| (which == 7 && iter >= NB_MOBTYPE))
		return (errno = 1, eerror("Obj/mob index too big."));
	if (which == 7)
		which = which + NB_OBJTYPE - 1;
	which += tmp;
	return (set_frames(gui, which, args[iter], num));
}

bool	set_frames(t_gui *gui, size_t which, char *path, int num)
{
	size_t	i;
	char	*numpath;

	if (!gui->textures.spfrsizes[which])
		gui->textures.spfrsizes[which] = abs(num) + !num;
	if (path && num < 0)
		return (load_texture_arr(gui, &gui->textures.spframes[which], path, -num));
	i = 0;
	while ((int)i < num)
	{
		numpath = get_numbered_texture_path(i, path);
		if (!numpath)
			return (put_parsing_err("Not enough memory."), true);
		if (load_texture_arr(gui, &gui->textures.spframes[which], numpath, num))
			return (free(numpath), true);
		free(numpath);
		i++;
	}
	return (false);
}
