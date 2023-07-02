/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:27:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/02 02:38:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	set_wall_texture(t_gui *gui, char *path, int idx)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	if (gui->textures.walls[idx])
		mlx_destroy_image(gui->mlx, gui->textures.walls[idx]);
	gui->textures.walls[idx] = mlx_xpm_file_to_image(gui->mlx, path,
			&width, &height);
	if (!gui->textures.walls[idx])
		return (put_parsing_err("Not enough memory"), true);
	return (false);
}

// floor == 0 && ceil == 0
static bool	set_ceilfloor_texture(t_gui *gui, char *path, int idx)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	if (!gui->textures.floorceil)
	{
		gui->textures.floorceil = malloc(3 * sizeof(*gui->textures.floorceil));
		if (!gui->textures.floorceil)
			return (put_parsing_err("Not enough memory."), true);
	}
	else if (gui->textures.floorceil[idx])
		mlx_destroy_image(gui->mlx, gui->textures.floorceil[idx]);
	gui->textures.floorceil[idx] = mlx_xpm_file_to_image(gui->mlx, path,
			&width, &height);
	if (!gui->textures.floorceil[idx])
		return (put_parsing_err("Not enough memory"), true);
	return (false);
}

bool	set_texture(t_gui *gui, char *line, enum e_type_identifier ti)
{
	char	*path;

	path = get_type_identifier_data(line);
	if (!path)
		return (true);
	if (ti == north_texture_path && set_wall_texture(gui, path, 0))
		return (true);
	else if (ti == south_texture_path && set_wall_texture(gui, path, 1))
		return (true);
	else if (ti == east_texture_path && set_wall_texture(gui, path, 2))
		return (true);
	else if (ti == west_texture_path && set_wall_texture(gui, path, 3))
		return (true);
	else if (ti == floor_texture_path && set_ceilfloor_texture(gui, path, 0))
		return (true);
	else if (ti == ceiling_texture_path && set_ceilfloor_texture(gui, path, 1))
		return (true);
	return (free(path), false);
}

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

bool	set_color(t_gui *gui, char *line, enum e_type_identifier ti)
{
	char	**split;
	size_t	i;
	int		rgb[4];

	split = ft_split(line, ',');
	if (!split)
		return (put_parsing_err("Not enough memory."), true);
	i = 0;
	rgb[i++] = 0;
	while (split[i])
	{
		rgb[i] = ft_atoi(split[i]);
		i++;
	}
	if (ti == ceiling_color)
		gui->textures.ceil_color = create_trgb(rgb[0], rgb[1], rgb[2], rgb[3]);
	else if (ti == floor_color)
		gui->textures.floor_color = create_trgb(rgb[0], rgb[1], rgb[2], rgb[3]);
	return (free_str_arr(split), false);
}
