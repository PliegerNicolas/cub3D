/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 06:54:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/19 12:20:09 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static bool	is_valid_map_line(char *line, char *charset)
{
	static bool	spawn_point_found;
	size_t		i;

	if (!line)
		return (true);
	if (!*line)
		return (put_parsing_err("Invalid map in *.cub file."), false);
	i = 0;
	while (line[i])
	{
		if (!is_incharset(line[i], charset) && !ft_isspace(line[i]))
			return (put_parsing_err("Invalid map in *.cub file : invalid charac\
ter found."), false);
		if (is_incharset(line[i], "NSWE"))
		{
			if (!spawn_point_found)
				spawn_point_found = true;
			else
				return (put_parsing_err("Invalid map in *.cub file : multiple s\
pawn points found."), false);
		}
		i++;
	}
	return (true);
}

bool	add_to_map_ctrl(t_map_ctrl **map_ctrl, char *line)
{
	t_map_ctrl	*temp;
	t_map_ctrl	*new_map_ctrl;

	temp = malloc(1 * sizeof(*temp));
	if (!temp)
		return (put_parsing_err("Not enough memory."), true);
	temp->line = ft_strdup(line);
	if (!temp->line)
		return (free(temp), put_parsing_err("Not enough memory."), true);
	temp->len = ft_strlen(temp->line);
	temp->next = NULL;
	if (!*map_ctrl)
		*map_ctrl = temp;
	else
	{
		new_map_ctrl = *map_ctrl;
		while (new_map_ctrl->next)
			new_map_ctrl = new_map_ctrl->next;
		new_map_ctrl->next = temp;
	}
	return (false);
}

bool	parse_map(char *line, t_map_ctrl **map_ctrl)
{
	if (!line)
		return (true);
	rm_eol(line);
	if (!is_valid_map_line(line, MAPTOKENS))
		return (true);
	if (add_to_map_ctrl(map_ctrl, line))
		return (true);
	return (false);
}
