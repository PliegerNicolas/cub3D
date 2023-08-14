/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:23:10 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/14 21:24:54 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

bool	set_weapon(t_gui *gui, char *line)
{
	char	*path;
	int		width;
	int		height;

	path = get_type_identifier_data(line);
	if (!path)
		return (true);
	width = 0;
	height = 0;
	if (gui->textures.weapon)
		mlx_destroy_image(gui->mlx, gui->textures.weapon);
	gui->textures.weapon = mlx_xpm_file_to_image(gui->mlx, path,
			&width, &height);
	if (!gui->textures.weapon)
		return (free(path), put_parsing_err("Not enough memory or invalid weapon texture"), true);
	return (free(path), false);
}
