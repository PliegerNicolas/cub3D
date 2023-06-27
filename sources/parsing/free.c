/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:36:49 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 03:19:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

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
