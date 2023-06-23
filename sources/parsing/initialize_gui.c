/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_gui.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:25:33 by nplieger          #+#    #+#             */
/*   Updated: 2023/06/23 17:23:56 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

bool	initialize_gui(t_gui *gui)
{
	// define mlx
	gui->mlx = mlx_init();
	if (!gui->mlx)
		return (put_parsing_err("Couldn't initialize graphical driver."), true);

	// Image buffer for screen size def
	//gui->buffer = mlx_new_image(gui->mlx, SCRWIDTH, SCRHEIGHT);
	gui->buffer = NULL;
	if (!gui->buffer)
		return (free(gui->mlx), put_parsing_err("Couldn't build image."), true);

	return (false);
}
