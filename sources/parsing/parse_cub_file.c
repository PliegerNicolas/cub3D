/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:09:00 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/02 02:51:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	retrieve_map(t_gui *gui, t_map_ctrl *map_ctrl)
{
	if (!map_ctrl)
		return (put_parsing_err("Map not found in *.cub file."), true);
	if (convert_map_ctrl_to_int_arr(gui, map_ctrl))
		return (free_map_ctrl(&map_ctrl), true);
	free_map_ctrl(&map_ctrl);
	if (set_player(gui))
		return (true);
	if (set_sprites(gui))
		return (true);
	if (!is_map_closed(gui))
		return (true);
	return (false);
}

static bool	textures_set(t_gui *gui)
{
	size_t	i;

	if (!gui->textures.walls)
		return (put_parsing_err("Missing wall textures."), true);
	i = 0;
	while (i < 4)
		if (!gui->textures.walls[i++])
			return (put_parsing_err("Missing wall textures."), true);
	return (false);
}

bool	parse_line(t_gui *gui, char *line, t_map_ctrl **map_ctrl,
	bool *is_commented)
{
	size_t					i;
	enum e_type_identifier	ti;
	static bool				map_found;

	if (!line)
		return (false);
	i = 0;
	skip_whitespaces(line, &i);
	skip_comments(line, &i, is_commented);
	if (!line[i] || (line[i] == '\n' && !map_found))
		return (false);
	ti = set_type_identifier(line, &i);
	if (line[i] && map_found == false && ti != not_found)
	{
		if (act_on_type_identifier(gui, line + i, ti))
			return (true);
	}
	else if (line[i] || map_found)
	{
		if (!map_found)
			map_found = true;
		if (parse_map(line, map_ctrl))
			return (free_map_ctrl(map_ctrl), true);
	}
	return (false);
}

bool	parse_cub_file(t_gui *gui, int fd)
{
	char		*line;
	t_map_ctrl	*map_ctrl;
	bool		is_commented;

	line = "";
	map_ctrl = NULL;
	is_commented = false;
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(gui, line, &map_ctrl, &is_commented))
			return (free(line), goto_eof(fd), true);
		free(line);
	}
	if (retrieve_map(gui, map_ctrl))
		return (true);
	if (textures_set(gui))
		return (true);
	return (false);
}
