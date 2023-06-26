/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:09:00 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/26 07:09:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

bool	is_type_identifier(char *line, size_t index)
{
	if (!line)
		return (false);
	if (ft_strncmp(line + index, "NO", 2) == 0)
		return (true);
	else if (ft_strncmp(line + index, "SO", 2) == 0)
		return (true);
	else if (ft_strncmp(line + index, "WE", 2) == 0)
		return (true);
	else if (ft_strncmp(line + index, "EA", 2) == 0)
		return (true);
	else if (ft_strncmp(line +index, "F", 1) == 0)
		return (true);
	else if (ft_strncmp(line + index, "C", 1) == 0)
		return (true);
	return (false);
}

bool	parse_cub_file(t_gui *gui, int fd)
{	
	char	*line;
	size_t	i;

	line = "";
	while (line)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		skip_whitespaces(line, &i);
		(void)skip_comments(line, &i);
		while (line[i])
		{
			if (skip_comments(line, &i))
				continue ;
			else if (is_type_identifier(line, i))
			{
				// set identifier
				printf("%s", line + i);
				break ;
			}
			else if (line[i] != '\n')
			{
				i = 0;
				// parse map
				printf("%s", line + i);
				break ;
			}
			i++;
		}
		free(line);
	}
	(void)gui;
	return (false);
}
