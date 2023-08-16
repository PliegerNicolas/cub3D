/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:18:25 by emis              #+#    #+#             */
/*   Updated: 2023/08/16 15:41:22 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	key_press(int keycode, t_gui *gui)
{
	int		keypress_index;

	if (keycode == XK_Escape)
		return (mlx_loop_end(gui->mlx));
	keypress_index = get_keypress_index(keycode);
	if (keypress_index >= 0)
		gui->keys |= (1 << keypress_index);
	return (0);
}

int	key_rel(int keycode, t_gui *gui)
{
	int		keypress_index;

	keypress_index = get_keypress_index(keycode);
	if (keypress_index >= 0)
		gui->keys &= ~(1 << keypress_index);
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_gui *gui)
{
	int			mousepress_index;
	static bool	capture;

	mousepress_index = get_mousepress_index(keycode);
	if (mousepress_index >= 0)
		gui->btns |= (1 << mousepress_index);
	if (!keycode)
		return (capture);
	else if (keycode == 2)
		capture = !capture;
	else if (keycode == 3)
	{
		change_render_type(&gui->cam.rndr);
		gui->rendered = 0;
	}
	else if (keycode == 4)
		gui->cam.dark = bind(gui->cam.dark + 1, 0, 0xFF);
	else if (keycode == 5)
		gui->cam.dark = bind(gui->cam.dark - 1, 0, 0xFF);
	return ((void)x, (void)y, capture);
}

int	mouse_rel(int keycode, int x, int y, t_gui *gui)
{
	int	mousepress_index;

	mousepress_index = get_mousepress_index(keycode);
	if (mousepress_index >= 0)
		gui->btns &= ~(1 << mousepress_index);
	return ((void)x, (void)y, 0);
}

int	mouse_motion(int x, int y, t_gui *gui)
{
	static int	last[2];

	initialize_mouse_motion(gui, last);
	if (x != last[0])
	{
		rotate(&gui->cam, (last[0] - x) / 4.0);
		gui->rendered = 0;
	}
	if (y != last[1])
	{
		pitch(&gui->cam, (last[1] - y) / 4.0);
		gui->rendered = 0;
	}
	last[0] = x;
	last[1] = y;
	if (mouse_press(0, 0, 0, gui))
	{
		x = loop_bind(x, 30, SCRWIDTH - 30);
		if (x != bind(last[0], 20, SCRWIDTH - 20))
		{
			mlx_mouse_move(gui->mlx, gui->win, x, y);
			last[0] = x;
		}
	}
	return (0);
}
