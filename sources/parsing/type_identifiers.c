/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_identifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 07:20:02 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 07:11:02 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

enum e_type_identifier	set_type_identifier(char *line, size_t *index)
{
	if (!line)
		return (not_found);
	if (ft_strncmp(line + *index, "NO", 2) == 0)
		return (*index += 2, north_texture_path);
	else if (ft_strncmp(line + *index, "SO", 2) == 0)
		return (*index += 2, south_texture_path);
	else if (ft_strncmp(line + *index, "WE", 2) == 0)
		return (*index += 2, west_texture_path);
	else if (ft_strncmp(line + *index, "EA", 2) == 0)
		return (*index += 2, east_texture_path);
	else if (ft_strncmp(line + *index, "F", 1) == 0)
		return (*index += 1, floor_color);
	else if (ft_strncmp(line + *index, "C", 1) == 0)
		return (*index += 1, ceiling_color);
	return (not_found);
}

/* This function should that "line + *i" as input given that the first */
/* characters represent the type identifier. */
bool	act_on_type_identifier(t_gui *gui, char *line,
	enum e_type_identifier ti)
{
	if (ti == not_found)
		return (false);
	if (ti == north_texture_path || ti == south_texture_path
		|| ti == east_texture_path || ti == west_texture_path)
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
