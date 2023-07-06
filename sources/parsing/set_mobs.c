/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mobs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 05:11:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/03 15:05:59 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/parsing.h"
# include "../../includes/graphics.h"

static char	*get_mob_texture_path(size_t i)
{
	char	*path;
	char	*temp;
	char	*index;

	index = ft_itoa(i);
	if (!index)
		return (put_parsing_err("Not enough memory."), NULL);
	temp = ft_strjoin("textures/solong/slime", index);
	free(index);
	if (!temp)
		return (put_parsing_err("Not enough memory."), NULL);
	path = ft_strjoin(temp, ".xpm");
	free(temp);
	if (!path)
		return (put_parsing_err("Not enough memory."), NULL);
	return (path);
}

static bool	set_frames(t_gui *gui, size_t nb, int width, int height)
{
	t_img	**frames;
	size_t	i;
	char	*path;

	frames = malloc(8 * sizeof(*frames));
	if (!frames)
		return (put_parsing_err("Not enough memory."), true);
	i = 0;
	while (i < 8)
		frames[i++] = NULL;
	gui->textures.sprites[nb].frames = frames;
	i = 0;
	while (i < 8)
	{
		path = get_mob_texture_path(i);
		if (!path)
			return (put_parsing_err("Not enough memory."), true);
		frames[i] = mlx_xpm_file_to_image(gui->mlx, path, &width, &height);
		if (!frames[i])
			return (put_parsing_err("Not enough memory."), true);
		free(path);
		i++;
	}
	return (false);
}

static void	set_mob_pos(t_gui *gui, size_t nb, size_t row, size_t col)
{
	gui->textures.sprites[nb].posi.x = row;
	gui->textures.sprites[nb].posi.y = col;
	if (gui->map.map)
		gui->map.map[row][col] = 0;
}

bool	set_mobs(t_gui *gui)
{
	size_t	nb;
	size_t	row;
	size_t	col;

	nb = 0;
	row = 0;
	while (row < gui->map.height)
	{
		col = 0;
		while (col < gui->map.width)
		{
			if (gui->map.map[row][col] == mob_tile)
			{
				set_mob_pos(gui, nb, row, col);
				if (set_frames(gui, nb++, 0, 0))
					return (true);
			}
			col++;
		}
		row++;
	}
	return (false);
}
