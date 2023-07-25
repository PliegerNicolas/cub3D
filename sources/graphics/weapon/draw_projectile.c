/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projectile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 01:43:35 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/26 01:44:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	draw_projectile(t_gui *gui, int x, int y, double distance)
{
	int		color;
	int		size;
	int		i;
	int		j;

	color = 0x9183EB;
	size = fmax(2, fmin(10, 10 - distance));
	i = x - (size / 2);
	while (i < x + (int)(size / 2))
	{
		j = y - size;
		while (j < y + (int)(size / 2))
		{
			if ((i - x) * (i - x) + (j - y) * (j - y) <= size * size / 4)
				pixput(gui->buffer, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_projectile_impact(t_gui *gui, int x, int y, double distance)
{
	int		color;
	int		size;
	int		i;
	int		j;

	color = 0x9183EB;
	size = fmax(4, fmin(15, 15 - distance));
	i = x - (size / 2);
	while (i < x + (int)(size / 2))
	{
		j = y - size;
		while (j < y + (int)(size / 2))
		{
			if ((i - x) * (i - x) + (j - y) * (j - y) <= size * size / 4)
			{
				if (rand() % 2)
					pixput(gui->buffer, i, j, color);
			}
			j++;
		}
		i++;
	}
}
