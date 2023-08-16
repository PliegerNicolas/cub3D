/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 03:27:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/16 11:00:01 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static bool	set_wall_texture(t_gui *gui, char *path, int idx)
{
	size_t	i;

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
			&gui->textures.width, &gui->textures.height);
	if (!gui->textures.walls[idx])
		return (put_parsing_err("Not enough memory or invalid texture"), true);
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
		return (put_parsing_err("Not enough memory or invalid texture"), true);
	return (false);
}

static bool	set_sprite_texture(t_gui *gui, char *path)
{
	char	**args;
	int		iter;
	int		which;
	const char *flds[] = {"HP\0\0", "STA\0", "ARM\0", "AMMO", "XP\0\0",
		".\0\0\0", "OBJ\0", "MOB\0"};

	args = ft_splitset(path, " \t,;");
	which = -1;
	iter = -1;
	while (args && args[0] && ++iter < 8)
		if (!ft_strncmp((char *)flds[iter], args[0], 4))
			which = iter;
	if (which == -1)
		return (free_ch_ar(args), errno = 1, eerror(E_SPTEXTID));
	if (args && args[0] && args[1])
		iter = ft_atoi(args[1]);
	if (!args[1] || iter == 0)
		return (free_ch_ar(args), errno = 1, eerror(E_SPTEXTNB));
	if (args && args[0] && args[1] && args[2] && which < LVL)
		iter = set_frames(gui, which, args[2], iter);
	if (args && args[0] && args[1] && args[2] && which > LVL)
		iter = set_mob_obj_frames(gui, which, args, iter);
	free_ch_ar(args);
	return (iter != 0);
}

static bool	set_which(t_gui *gui, t_type_id ti, char *path)
{
	int				i;
	const t_type_id	floor_and_ceiling[2] = {floor_texture, ceiling_texture};
	const t_type_id	walls[4] = {north_texture, south_texture,
		west_texture, east_texture};

	if (ti == sprite_texture)
		return (set_sprite_texture(gui, path));
	if (ti == door_texture)
		return (load_texture_arr(gui, &gui->textures.doors, path, 1));
	i = -1;
	while ((size_t)++i < sizeof(walls) / sizeof(*walls))
		if (ti == walls[i] && set_wall_texture(gui, path, i))
			return (true);
	i = -1;
	while ((size_t)++i < sizeof(floor_and_ceiling) / sizeof(*floor_and_ceiling))
		if (ti == floor_and_ceiling[i] && set_floorceil_texture(gui, path, i))
			return (true);
	return (false);
}

bool	set_texture(t_gui *gui, char *line, t_type_id ti)
{
	char		*path;

	path = get_type_identifier_data(line);
	if (!path)
		return (true);
	if (set_which(gui, ti, path))
		return (free(path), true);
	return (free(path), false);
}
