/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_filter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:45:05 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/01 22:50:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	rm_eol(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		line[i] = '\0';
}

void	skip_whitespaces(char *line, size_t *i)
{
	if (!line)
		return ;
	while (line[*i] && line[*i] != '\n' && ft_isspace(line[*i]))
		(*i)++;
}

void	skip_comments(char *line, size_t *i, bool *is_commented)
{
	if (!line)
		return ;
	if (*is_commented)
	{
		while (line[*i] && ft_strncmp(line + *i, "*/", 2) != 0)
			(*i)++;
		if (ft_strncmp(line + *i, "*/", 2) == 0)
		{
			(*i) += 2;
			*is_commented = false;
		}
	}
	else
	{
		if (line[*i] && ft_strncmp(line + *i, "//", 2) == 0)
			while (line[*i])
				(*i)++;
		else if (line[*i] && ft_strncmp(line + *i, "/*", 2) == 0)
		{
			(*i) += 2;
			*is_commented = true;
			skip_comments(line, i, is_commented);
		}
	}
}

/*
void	skip_comments(char *line, size_t *i, bool *is_commented)
{
	if (!line)
		return ;
	if (*is_commented)
	{
		while (line[*i])
		{
			if (ft_strncmp(line + *i, "\*\/", 2) != 0)
				(*i)++;
			else
			{
				(*i) += 2;
				*is_commented = false;
				return ;
			}
		}
	}
	else
	{
		if (line[*i] && ft_strncmp(line + *i, "//", 2) == 0)
			while (line[*i])
				(*i)++;
		else if (line[*i] && ft_strncmp(line + *i, "\/\*", 2) == 0)
		{
			(*i) += 2;
			*is_commented = true;
			skip_comments(line, i, is_commented);
		}
	}
}
*/
