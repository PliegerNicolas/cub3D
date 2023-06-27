/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:17:24 by nplieger          #+#    #+#             */
/*   Updated: 2023/06/27 03:04:32 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	initialize_sprites(t_gui *gui)
{
	(void)gui;
	return (false);
}

static bool initialize_textures(t_gui *gui)
{
	size_t	i;

	gui->textures.height = 32;
	gui->textures.width = 32;
	gui->textures.arrsize = 4;
	gui->textures.floor_color = 0;
	gui->textures.ceil_color = 0;
	gui->textures.walls = NULL;
	gui->textures.floorceil = NULL;
	gui->textures.walls = malloc(4 * sizeof(*gui->textures.walls));
	if (!gui->textures.walls)
		return (put_parsing_err("Not enough memory."), true);
	i = 0;
	while (i < 4)
		gui->textures.walls[i++] = NULL;
	gui->textures.floorceil = malloc(2 * sizeof(*gui->textures.floorceil));
	if (!gui->textures.floorceil)
		return (put_parsing_err("Not enough memory."), true);
	i = 0;
	while (i < 2)
		gui->textures.floorceil[i++] = NULL;
	return (false);
}

static bool	initialize_gui(t_gui *gui)
{
	gui->mlx = mlx_init();
	if (!gui->mlx)
	{
		put_parsing_err("Couldn't initialize graphical driver.");
		return (clear_parsing(gui), true);
	}
	gui->buffer = mlx_new_image(gui->mlx, SCRWIDTH, SCRHEIGHT);
	if (!gui->buffer)
	{
		put_parsing_err("Couldn't build image.");
		return (clear_parsing(gui), put_parsing_err("Couldn't build image."), true);
	}
	if (initialize_sprites(gui))
		return (clear_parsing(gui), true);
	if (initialize_textures(gui))
		return (clear_parsing(gui), true);
	gui->keys = 0;
	gui->rendered = 0;
	return (false);
}

bool	initialize(int argc, char **argv, t_gui *gui)
{
	int	fd;

	if (verify_arguments(argc, argv))
		return (true);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (put_parsing_err("Unable to open file."), true);
	if (initialize_gui(gui))
		return (close(fd), true);
	if (parse_cub_file(gui, fd))
		return (close(fd), true);
	return (close(fd), false);
}
