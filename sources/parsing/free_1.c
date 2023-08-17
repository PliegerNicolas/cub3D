/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:36:49 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/17 15:48:34 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	free_map(t_gui *gui)
{
	size_t	i;

	if (!gui->map.map)
		return ;
	i = 0;
	while (i < gui->map.height)
	{
		if (gui->map.map[i])
			free(gui->map.map[i]);
		else
			break ;
		i++;
	}
	free(gui->map.map);
}

static void	free_textures(t_gui *gui)
{
	size_t	i;

	if (gui->textures.walls)
	{
		i = 0;
		while (i < 4)
		{
			if (gui->textures.walls[i])
				mlx_destroy_image(gui->mlx, gui->textures.walls[i]);
			i++;
		}
		free(gui->textures.walls);
	}
	if (gui->textures.floorceil)
	{
		i = 0;
		while (i < 2)
		{
			if (gui->textures.floorceil[i])
				mlx_destroy_image(gui->mlx, gui->textures.floorceil[i]);
			i++;
		}
		free(gui->textures.floorceil);
	}
}

void	clear_parsing(t_gui *gui)
{
	if (!gui->mlx)
		return ;
	free_textures(gui);
	free_map(gui);
	if (gui->buffer)
		mlx_destroy_image(gui->mlx, gui->buffer);
}
