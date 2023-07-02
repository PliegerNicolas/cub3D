/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_int_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 02:31:54 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/30 02:48:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"

void	free_int_arr(int **int_arr, size_t rowsize)
{
	size_t	row;

	if (!int_arr)
		return ;
	row = 0;
	while (row < rowsize)
	{
		if (int_arr[row])
			free(int_arr[row]);
		else
			break ;
		row++;
	}
	free(int_arr);
}

int	**copy_int_arr(int **arr, size_t rowsize, size_t colsize)
{
	int		**new;
	size_t	row;
	size_t	col;

	new = malloc(rowsize * sizeof(*new));
	if (!new)
		return (NULL);
	row = 0;
	while (row < rowsize)
	{
		new[row] = malloc(colsize * sizeof(**new));
		if (!new[row])
			return (free_int_arr(new, row), NULL);
		col = 0;
		while (col < colsize)
		{
			new[row][col] = arr[row][col];
			col++;
		}
		row++;
	}
	return (new);
}
