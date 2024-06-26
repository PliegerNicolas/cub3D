/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_identifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 07:20:02 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/19 12:05:41 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "graphics.h"

static void	set_strti(t_str_to_ti *strti)
{
	strti[0].str = "NO";
	strti[0].ti = north_texture;
	strti[1].str = "SO";
	strti[1].ti = south_texture;
	strti[2].str = "WE";
	strti[2].ti = west_texture;
	strti[3].str = "EA";
	strti[3].ti = east_texture;
	strti[4].str = "F";
	strti[4].ti = floor_color;
	strti[5].str = "C";
	strti[5].ti = ceiling_color;
	if (!BONUS)
		return ;
	strti[6].str = "FL";
	strti[6].ti = floor_texture;
	strti[7].str = "CE";
	strti[7].ti = ceiling_texture;
	strti[8].str = "D";
	strti[8].ti = door_texture;
	strti[9].str = "SP";
	strti[9].ti = sprite_texture;
	strti[10].str = "WP";
	strti[10].ti = weapon_texture;
}

t_type_id	set_type_identifier(char *line, size_t *index)
{
	size_t		i;
	size_t		len;
	t_str_to_ti	strti[6 + (5 * BONUS)];

	if (!line)
		return (not_found);
	set_strti(strti);
	i = 0;
	while (i < sizeof(strti) / sizeof(*strti))
	{
		len = 0;
		while ((line + *index)[len] && !ft_isspace((line + *index)[len]))
			len++;
		if (ft_strncmp(line + *index, strti[i].str, len) == 0)
			return ((*index) += len, strti[i].ti);
		i++;
	}
	return (not_found);
}

/* This function takes "line + *i" as argument. The first given characters of */
/* line + i should be the type identifier characters represent the type */
/* identifier. */
bool	act_on_type_identifier(t_gui *gui, char *line, t_type_id ti)
{
	rm_eol(line);
	if (ti == not_found)
		return (false);
	if (ti == north_texture || ti == south_texture
		|| ti == east_texture || ti == west_texture
		|| ti == floor_texture || ti == ceiling_texture
		|| ti == door_texture || ti == sprite_texture
		|| ti == weapon_texture)
	{
		if (set_texture(gui, line, ti))
			return (true);
	}
	else if (ti == floor_color || ti == ceiling_color)
	{
		if (set_color(gui, line, ti))
			return (true);
	}
	return (false);
}
