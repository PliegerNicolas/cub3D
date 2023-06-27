/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_ctrl_to_int_arr.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:13:03 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/27 18:22:59 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	set_map_sizes(t_gui *gui, t_map_ctrl *map_ctrl)
{
	t_map_ctrl	*temp;
	size_t		nodes;
	
	temp = map_ctrl;
	nodes = 0;
	gui->map.width = 0;
	while (temp)
	{
		if (temp->len > gui->map.width)
			gui->map.width = temp->len;
		nodes++;
		temp = temp->next;
	}
	gui->map.height = nodes;
}

static int	**malloc_map(t_gui *gui)
{
	int		**map;
	size_t	i;

	map = malloc(gui->map.height * sizeof(*map));
	if (!map)
		return (put_parsing_err("Not enough memory."), map);
	i = 0;
	while (i < gui->map.height)
	{
		map[i] = malloc(gui->map.width * sizeof(**map));
		if (!map[i])
			return (put_parsing_err("Not enough memory."), map);
		i++;
	}
	return (map);
}

bool	convert_map_ctrl_to_int_arr(t_gui *gui, t_map_ctrl *map_ctrl)
{
	set_map_sizes(gui, map_ctrl);
	gui->map.map = malloc_map(gui);
	if (!gui->map.map)
		return (true);
	printf("Width = %ld, Height = %ld\n", gui->map.width, gui->map.height);
	(void)gui;
	(void)map_ctrl;
	return (false);
}
