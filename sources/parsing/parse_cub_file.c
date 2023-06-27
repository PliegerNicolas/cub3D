/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:09:00 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 07:42:33 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	parse_line(t_gui *gui, char *line, size_t *i)
{
	enum e_type_identifier	ti;

	while (line[*i])
	{
		if (skip_comments(line, i))
			continue ;
		ti = set_type_identifier(line, i);
		if (line[*i] && ti != not_found)
		{
			if (act_on_type_identifier(gui, line + *i, ti))
				return (true);
			break ;
		}
		else if (line[*i] && line[*i] != '\n')
		{
			*i = 0;
			if (parse_map(gui, line))
				return (true);
			break ;
		}
		else
			(*i)++;
	}
	return (false);
}

bool	parse_cub_file(t_gui *gui, int fd)
{	
	char				*line;
	size_t				i;

	line = "";
	while (line)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		skip_whitespaces(line, &i);
		(void)skip_comments(line, &i);
		if (parse_line(gui, line, &i))
			return (free(line), true);
		free(line);
	}
	return (false);
}
