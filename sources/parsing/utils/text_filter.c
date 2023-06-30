/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:45:05 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/26 07:08:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	skip_whitespaces(char *line, size_t *index)
{
	if (!line)
		return ;
	while (line[*index] && ft_isspace(line[*index]))
		(*index)++;
}

int	skip_comments(char *line, size_t *index)
{
	if (!line)
		return (0);
	if (ft_strncmp(line + *index, "//", 2) == 0)
	{
		*index += 2;
		while (line[*index])
			(*index)++;
		return (1);
	}
	else if (ft_strncmp(line + *index, "/*", 2) == 0)
	{
		*index += 2;
		while (line[*index])
		{
			if (ft_strncmp(line + *index, "*/", 2) == 0)
				return (*index += 2, 1);
			(*index)++;
		}
	}
	return (0);
}
