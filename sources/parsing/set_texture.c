/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:27:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/03 18:36:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	set_wall_texture(t_gui *gui, char *path, int idx)
{
	size_t	i;
	int		width;
	int		height;

	width = 0;
	height = 0;
	if (!gui->textures.walls)
	{
		gui->textures.walls = malloc(5 * sizeof(*gui->textures.walls));
		if (!gui->textures.walls)
			return (put_parsing_err("Not enough memory."), true);
		i = 0;
		while (i < 5)
			gui->textures.walls[i++] = NULL;
	}
	if (gui->textures.walls[idx])
	{
		mlx_destroy_image(gui->mlx, gui->textures.walls[idx]);
		gui->textures.walls[idx] = NULL;
	}
	gui->textures.walls[idx] = mlx_xpm_file_to_image(gui->mlx, path,
			&width, &height);
	if (!gui->textures.walls[idx])
		return (put_parsing_err("Not enough memory"), true);
	return (false);
}

static bool	set_floorceil_texture(t_gui *gui, char *path, int idx)
{
	size_t	i;
	int		width;
	int		height;

	width = 0;
	height = 0;
	if (!gui->textures.floorceil)
	{
		gui->textures.floorceil = malloc(3 * sizeof(*gui->textures.floorceil));
		if (!gui->textures.floorceil)
			return (put_parsing_err("Not enough memory."), true);
		i = 0;
		while (i < 3)
			gui->textures.floorceil[i++] = NULL;
	}
	else if (gui->textures.floorceil[idx])
	{
		mlx_destroy_image(gui->mlx, gui->textures.floorceil[idx]);
		gui->textures.floorceil[idx] = NULL;
	}
	gui->textures.floorceil[idx] = mlx_xpm_file_to_image(gui->mlx, path,
			&width, &height);
	if (!gui->textures.floorceil[idx])
		return (put_parsing_err("Not enough memory"), true);
	return (false);
}

static void	initialize_walls_enum_tab(t_type_id *type_ids)
{
	type_ids[0] = north_texture;
	type_ids[1] = south_texture;
	type_ids[2] = west_texture;
	type_ids[3] = east_texture;
}

static void	initialize_floorceil_enum_tab(t_type_id *type_ids)
{
	type_ids[0] = floor_texture;
	type_ids[1] = ceiling_texture;
}

bool	set_texture(t_gui *gui, char *line, t_type_id ti)
{
	char		*path;
	size_t		i;
	t_type_id	walls[4];
	t_type_id	floor_and_ceiling[2];

	path = get_type_identifier_data(line);
	if (!path)
		return (true);
	initialize_walls_enum_tab(walls);
	initialize_floorceil_enum_tab(floor_and_ceiling);
	i = 0;
	while (i < sizeof(walls) / sizeof(*walls))
	{
		if (ti == walls[i] && set_wall_texture(gui, path, i))
			return (free(path), true);
		i++;
	}
	i = 0;
	while (i < sizeof(floor_and_ceiling) / sizeof(*floor_and_ceiling))
	{
		if (ti == floor_and_ceiling[i] && set_floorceil_texture(gui, path, i))
			return (free(path), true);
		i++;
	}
	return (free(path), false);
}