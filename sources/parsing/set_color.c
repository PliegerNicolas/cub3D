/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:33:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/08 05:49:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static bool	get_rgb_colors(char **split, int *rgb)
{
	size_t	i;

	if (!split)
		return (false);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		return (put_parsing_err("Invalid RGB color given."), true);
	i = 0;
	while (split[i])
	{
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (put_parsing_err("Invalid RGB color given."), true);
		i++;
	}
	return (false);
}

bool	set_color(t_gui *gui, char *line, t_type_id ti)
{
	char	*path;
	char	**split;
	int		rgb[3];

	path = get_type_identifier_data(line);
	if (!path)
		return (put_parsing_err("Not enough memory."), true);
	split = ft_split(path, ',');
	free(path);
	if (!split)
		return (put_parsing_err("Not enough memory."), true);
	if (get_rgb_colors(split, rgb))
		return (free_str_arr(split), true);
	if (ti == ceiling_color)
		gui->textures.ceil_color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	else if (ti == floor_color)
		gui->textures.floor_color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	return (free_str_arr(split), false);
}
