/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:09:00 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 14:05:49 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	parse_line(t_gui *gui, char *line, size_t *i, t_map_ctrl **map_ctrl)
{
	enum e_type_identifier	ti;
	static bool				map_found;

	while (line[*i])
	{
		if (skip_comments(line, i))
			continue ;
		ti = set_type_identifier(line, i);
		if (line[*i] && ti != not_found && !map_found)
		{
			if (act_on_type_identifier(gui, line + *i, ti))
				return (true);
			break ;
		}
		else if (line[*i] && line[*i] != '\n')
		{
			map_found = true;
			if (parse_map(gui, line, map_ctrl))
				return (free_map_ctrl(map_ctrl), true);
			break ;
		}
		else
			(*i)++;
	}
	return (false);
}

bool	parse_cub_file(t_gui *gui, int fd)
{
	t_map_ctrl	*map_ctrl;
	char		*line;
	size_t		i;

	line = "";
	map_ctrl = NULL;
	while (line)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		skip_whitespaces(line, &i);
		(void)skip_comments(line, &i);
		if (parse_line(gui, line, &i, &map_ctrl))
			return (free(line), true);
		free(line);
	}
	if (!map_ctrl)
		return (true);
	return (free_map_ctrl(&map_ctrl), false);
}
