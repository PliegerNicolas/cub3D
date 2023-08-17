/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:23:10 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/17 17:50:56 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static size_t	count_args(char **args)
{
	size_t	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

static int	find_open_weapon_slot(t_img ***texture_arr)
{
	int		which;

	if (!texture_arr)
		return (put_parsing_err("Not enough memory"), -1);
	which = SIZE + NB_OBJTYPE + NB_MOBTYPE;
	while (texture_arr[which])
		which++;
	if (which < SIZE + NB_OBJTYPE + NB_MOBTYPE + NB_WPNTYPE)
		return (which);
	return (put_parsing_err("Too much weapon textures set"), -1);
}

bool	set_weapon_texture(t_gui *gui, char *path)
{
	char	**args;
	int		which;
	int		iter;

	args = ft_splitset(path, " \t,;");
	if (!args)
		return (put_parsing_err("Not enough memory"), true);
	if (count_args(args) != 2)
		return (free_ch_ar(args), put_parsing_err("Incorrect WP format in .cub \
file : WP [frames] [texture_path]"), true);
	which = find_open_weapon_slot(gui->textures.spframes);
	if (which < 0)
		return (free_ch_ar(args), true);
	iter = ft_atoi(args[0]);
	if (iter <= 0)
		iter = 1;
	iter = set_frames(gui, which, args[1], iter);
	return (free_ch_ar(args), iter != 0);
}
