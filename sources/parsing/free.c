/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:36:49 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 16:43:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	read_rest_of_file(int fd)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(fd);
		free(line);
	}
}

void	free_map_ctrl(t_map_ctrl **map_ctrl)
{
	t_map_ctrl	*temp;

	if (!*map_ctrl)
		return ;
	while (*map_ctrl)
	{
		temp = (*map_ctrl)->next;
		if ((*map_ctrl)->line)
			free((*map_ctrl)->line);
		free(*map_ctrl);
		*map_ctrl = temp;
	}
	*map_ctrl = NULL;
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
