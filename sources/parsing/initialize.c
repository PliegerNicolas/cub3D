/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:17:24 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/17 15:47:43 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static bool	initialize_sprites(t_gui *gui)
{
	gui->textures.spnb = 0;
	gui->textures.sprites = NULL;
	return (false);
}

static bool	initialize_textures(t_gui *gui)
{
	gui->textures.arrsize = 4;
	gui->textures.floor_color = 0;
	gui->textures.ceil_color = 0;
	gui->textures.walls = NULL;
	gui->textures.doors = NULL;
	gui->textures.floorceil = NULL;
	if (BONUS)
	{
		gui->textures.ceil_color = 0x8DC2D9;
		gui->textures.floor_color = 0x6E6E6E;
	}
	else
	{
		gui->textures.ceil_color = -1;
		gui->textures.floor_color = -1;
	}
	ft_bzero(gui->textures.spframes, sizeof(gui->textures.spframes));
	ft_bzero(gui->textures.spfrsizes, sizeof(gui->textures.spfrsizes));
	return (false);
}

static bool	initialize_gui(t_gui *gui)
{
	gui->mlx = mlx_init();
	mkorbrk(gui->mlx, mlxwrap, !gui->mlx, 1);
	gui->buffer = mlx_new_image(gui->mlx, SCRWIDTH, SCRHEIGHT);
	if (!gui->buffer)
	{
		put_parsing_err("Couldn't build image.");
		return (clear_parsing(gui), true);
	}
	if (initialize_sprites(gui))
		return (clear_parsing(gui), true);
	if (initialize_textures(gui))
		return (clear_parsing(gui), true);
	gui->keys = 0;
	gui->rendered = 0;
	gui->btns = 0;
	gui->map.map = NULL;
	return (false);
}

bool	initialize(int argc, char **argv, t_gui *gui)
{
	int	fd;

	if (verify_arguments(argc, argv))
		return (true);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		put_parsing_err("Unable to open file.");
		return (clear_parsing(gui), true);
	}
	if (initialize_gui(gui))
		return (clear_parsing(gui), close(fd), true);
	if (parse_cub_file(gui, fd))
		return (clear_parsing(gui), close(fd), true);
	return (close(fd), false);
}
