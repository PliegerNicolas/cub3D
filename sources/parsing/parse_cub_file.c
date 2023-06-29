/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:09:00 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/29 06:33:11 by nicolas          ###   ########.fr       */
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
		else if (line[*i] && (line[*i] != '\n' || map_found))
		{
			map_found = true;
			if (parse_map(line, map_ctrl))
				return (free_map_ctrl(map_ctrl), true);
			break ;
		}
		else
			(*i)++;
	}
	return (false);
}

static bool	retrieve_map(t_gui *gui, t_map_ctrl *map_ctrl)
{
	if (!map_ctrl)
		return (true);
	if (convert_map_ctrl_to_int_arr(gui, map_ctrl))
		return (free_map_ctrl(&map_ctrl), true);
	free_map_ctrl(&map_ctrl);
	if (!is_map_closed(gui))
		return (true);
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
		if (line[i] && line[i] != '\n')
			skip_whitespaces(line, &i);
		(void)skip_comments(line, &i);
		if (parse_line(gui, line, &i, &map_ctrl))
			return (free(line), goto_eof(fd), true);
		free(line);
	}
	if (retrieve_map(gui, map_ctrl))
		return (true);
	return (false);
}
