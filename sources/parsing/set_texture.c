/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:27:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 09:08:03 by nplieger         ###   ########.fr       */
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
	return (free(path), false);
}

bool	set_color(t_gui *gui, char *line, enum e_type_identifier ti)
{
	(void)gui;
	(void)line;
	(void)ti;
	return (false);
}
