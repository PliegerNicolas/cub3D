/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 04:58:12 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/13 12:37:12 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

void	free_str_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
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
