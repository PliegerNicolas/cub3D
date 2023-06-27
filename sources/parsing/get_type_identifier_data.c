/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_identifier_data.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 09:04:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/26 09:09:49 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

static size_t	get_data_len(char *line)
{
	size_t	i;
	size_t	j;

	if (!line)
		return (0);
	i = 0;
	j = 0;
	while (line[i + j] && line[i + j] != '\n')
	{
		if (skip_comments(line + i, &j))
			continue ;
		i++;
	}
	return (i);
}

char	*get_type_identifier_data(char *line)
{
	char	*data_str;
	size_t	i;
	size_t	j;

	if (!line)
		return (NULL);
	while (*line && ft_isspace(*line))
		line++;
	data_str = malloc((get_data_len(line) + 1) * sizeof(*data_str));
	if (!data_str)
		return (put_parsing_err("Not enough memory."), NULL);
	i = 0;
	j = 0;
	while (line[i + j] && line[i + j] != '\n')
	{
		if (skip_comments(line + i, &j))
			continue ;
		data_str[i] = line[i + j];
		i++;
	}
	data_str[i] = '\0';
	return (data_str);
}
