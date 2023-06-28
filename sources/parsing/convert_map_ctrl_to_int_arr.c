/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_ctrl_to_int_arr.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:13:03 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/28 18:02:58 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

/*
static void	put_map(t_gui *gui, t_map_ctrl *map_ctrl)
{
	t_map_ctrl	*temp;
	size_t		i;
	size_t		j;

	i = 0;
	temp = map_ctrl;
	while (i < gui->map.height)
	{
		j = 0;
		while (j < gui->map.width)
		{
			if (gui->map.map[i][j] == -1)
				printf(" ");
			else
				printf("%d", gui->map.map[i][j]);
			j++;
		}
		printf("\n");
		temp = temp->next;
		i++;
	}
}
*/

static int	convert_charmap_to_intmap(char c)
{
	if (c == ' ')
		return (-1);
	else if (c == '0')
		return (0);
	else if (c == '1')
		return (1);
	else if (c == 'N')
		return (2);
	else if (c == 'S')
		return (3);
	else if (c == 'W')
		return (4);
	else if (c == 'E')
		return (5);
	return (-1);
}

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

static void	write_to_map(t_gui *gui, t_map_ctrl *map_ctrl)
{
	t_map_ctrl	*temp;
	size_t		i;
	size_t		j;

	temp = map_ctrl;
	i = 0;
	while (i < gui->map.height)
	{
		j = 0;
		while (j < ft_strlen(temp->line))
		{
			gui->map.map[i][j] = convert_charmap_to_intmap(temp->line[j]);
			j++;
		}
		while (j < gui->map.width)
			gui->map.map[i][j++] = convert_charmap_to_intmap(' ');
		temp = temp->next;
		i++;
	}
}

//put_map(gui, map_ctrl);
bool	convert_map_ctrl_to_int_arr(t_gui *gui, t_map_ctrl *map_ctrl)
{
	set_map_sizes(gui, map_ctrl);
	gui->map.map = malloc_map(gui);
	if (!gui->map.map)
		return (true);
	write_to_map(gui, map_ctrl);
	return (false);
}
