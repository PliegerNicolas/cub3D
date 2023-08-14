/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:32:55 by nplieger          #+#    #+#             */
/*   Updated: 2023/08/14 11:49:44 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	draw_crosshair(t_gui *gui, int color)
{
	int	x;
	int	y;
	int	x_screen_center;
	int	y_screen_center;

	x_screen_center = (SCRWIDTH / 2.0);
	y_screen_center = (SCRHEIGHT / 2.0) + (gui->cam.pitch * SCRHEIGHT);
	x = (SCRWIDTH / 2) - 5;
	while (x < x_screen_center + 5
		&& y_screen_center < SCRHEIGHT - 5 && y_screen_center > 5)
		pixput(gui->buffer, x++, y_screen_center, color);
	y = y_screen_center - 5;
	while (y > 0 && y < SCRHEIGHT && y < y_screen_center + 5)
		pixput(gui->buffer, x_screen_center, y++, color);
}
