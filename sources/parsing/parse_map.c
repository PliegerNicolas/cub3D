/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 06:54:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 16:47:59 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	rm_eol(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = '\0';
}

static bool	is_valid_map_line(char *line, char *charset)
{
	size_t	i;

	if (!line)
		return (true);
	if (!*line)
		return (put_parsing_err("Invalid map in *.cub file."), false);
	i = 0;
	while (line[i])
	{
		if (!is_incharset(line[i], charset) && !ft_isspace(line[i]))
			return (put_parsing_err("Invalid map in *.cub file."), false);
		i++;
	}
	return (true);
}

bool	parse_map(t_gui *gui, char *line, t_map_ctrl **map_ctrl)
{
	if (!line)
		return (true);
	rm_eol(line);
	if (!is_valid_map_line(line, "01NSWE"))
		return (true);
	if (!*map_ctrl)
	{
		*map_ctrl = malloc(1 * sizeof(**map_ctrl));
		if (!*map_ctrl)
			return (put_parsing_err("Not enough memory."), true);
		(*map_ctrl)->line = ft_strdup(line);
		if (!(*map_ctrl)->line)
			return (put_parsing_err("Not enough memory."), true);
		(*map_ctrl)->len = ft_strlen((*map_ctrl)->line);
		(*map_ctrl)->next = NULL;
	}
	printf("%s\n", line);
	(void)map_ctrl;
	(void)gui;
	return (false);
}
