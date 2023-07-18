/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:58:29 by nplieger          #+#    #+#             */
/*   Updated: 2023/07/18 15:01:16 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	draw_crosshair(t_gui *gui, int color)
{
	size_t	x;
	size_t	y;
	size_t	x_screen_center;
	size_t	y_screen_center;

	x_screen_center = SCRWIDTH * 0.5;
	y_screen_center = SCRHEIGHT * 0.5;
	x = (SCRWIDTH / 2) - 5;
	while (x < x_screen_center + 5)
		pixput(gui->buffer, x++, y_screen_center, color);
	y = y_screen_center - 5;
	while (y < y_screen_center + 5)
		pixput(gui->buffer, x_screen_center, y++, color);
}
