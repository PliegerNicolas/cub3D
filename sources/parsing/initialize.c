/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:17:24 by nplieger          #+#    #+#             */
/*   Updated: 2023/06/26 07:12:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	initialize_gui(t_gui *gui)
{
	// define mlx
	gui->mlx = mlx_init();
	if (!gui->mlx)
		return (put_parsing_err("Couldn't initialize graphical driver."), true);

	// Image buffer for screen size def
	gui->buffer = mlx_new_image(gui->mlx, SCRWIDTH, SCRHEIGHT);
	if (!gui->buffer)
	{
		mlx_destroy_display(gui->mlx);
		free(gui->mlx);
		return (put_parsing_err("Couldn't build image."), true);
	}

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
