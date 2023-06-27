/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:36:49 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 07:25:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	free_map_constructor(t_map_constructor *map_constructor)
{
	t_map_constructor *temp;

	while (map_constructor->next)
	{
		temp = map_constructor->next;
		if (map_constructor->line)
			free(map_constructor->line);
		free(map_constructor);
		map_constructor = temp;
	}
	map_constructor = NULL;
}

void	free_textures(t_gui *gui)
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
	if (gui->buffer)
		mlx_destroy_image(gui->mlx, gui->buffer);
	mlx_destroy_display(gui->mlx);
	free(gui->mlx);
}
