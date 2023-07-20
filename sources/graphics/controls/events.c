/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:18:25 by emis              #+#    #+#             */
/*   Updated: 2023/07/18 04:16:13 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	key_press(int keycode, t_gui *gui)
{
	t_kbind	keys[12];
	size_t	i;

	if (keycode == XK_Escape)
		return (mlx_loop_end(gui->mlx));
	set_keys_arr(keys);
	i = 0;
	while (i < sizeof(keys) / sizeof(*keys))
	{
		if (keycode == (int)keys[i])
			gui->keys |= (1 << i);
		i++;
	}
	return (0);
}

int	key_rel(int keycode, t_gui *gui)
{
	t_kbind	keys[12];
	size_t	i;

	set_keys_arr(keys);
	i = 0;
	while (i < sizeof(keys) / sizeof(*keys))
	{
		if (keycode == (int)keys[i])
			gui->keys &= ~(1 << i);
		i++;
	}
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_gui *gui)
{
	t_bprs		btns[6];
	static bool	capture;
	size_t		i;

	set_btns_arr(btns);
	i = 0;
	while (i < sizeof(btns) / sizeof(*btns))
	{
		if (keycode == (int)btns[i])
			gui->btns |= (1 << i);
		i++;
	}
	if (!keycode)
		return (capture);
	else if (keycode == 2)
		capture = !capture;
	else if (keycode == 3)
	{
		gui->cam.rndr = (gui->cam.rndr + 1) % (FLOORCEIL + 1);
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
	t_bprs	btns[6];
	size_t	i;

	set_btns_arr(btns);
	i = 0;
	while (i < sizeof(btns) / sizeof(*btns))
	{
		if (keycode == (int)btns[i])
			gui->btns &= ~(1 << i);
		i++;
	}
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
