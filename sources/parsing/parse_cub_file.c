/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:09:00 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/26 09:14:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	parse_line(t_gui *gui, char *line, size_t *i)
{
	enum type_identifier	ti;

	while (line[*i])
	{
		if (skip_comments(line, i))
			continue ;
		ti = set_type_identifier(line, i);
		if (ti != not_found)
		{
			if (act_on_type_identifier(gui, line + *i, ti))
				return (true);
			break ;
		}
		else if (line[*i] != '\n')
		{
			*i = 0;
			// parse map
			printf("%s", line + *i);
			break ;
		}
		else
			(*i)++;
	}
	return (false);
}

bool	parse_cub_file(t_gui *gui, int fd)
{	
	char					*line;
	size_t					i;

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
