/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:18:25 by emis              #+#    #+#             */
/*   Updated: 2023/07/08 11:50:23 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

int	key_press(int keycode, t_gui *gui)
{
	int	i;

	if (keycode == XK_Escape)
		return (mlx_loop_end(gui->mlx));
	i = -1;
	while ((__u_int)++i < sizeof(KEYS) / sizeof(*KEYS))
		if (keycode == (int)KEYS[i])
			gui->keys |= (1 << i);
	return (0);
}

int	key_rel(int keycode, t_gui *gui)
{
	int	i;

	i = -1;
	while ((__u_int)++i < sizeof(KEYS) / sizeof(*KEYS))
		if (keycode == (int)KEYS[i])
			gui->keys &= ~(1 << i);
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_gui *gui)
{
	static _Bool	capture;
	int	i;

	i = -1;
	while ((__u_int)++i < sizeof(BTNS) / sizeof(*BTNS))
		if (keycode == (int)BTNS[i])
			gui->btns |= (1 << i);
	if (!keycode)
		return (capture);
	if (keycode == 2)
	{
		capture = !capture;
		// if (capture)
		// 	mlx_mouse_hide(gui->mlx, gui->mlx->win_list);
		// else
		// 	mlx_mouse_show(gui->mlx, gui->mlx->win_list);
	}
	if (keycode == 3)
		gui->cam.rndr = (gui->cam.rndr + 1) % (FLOORCEIL + 1), gui->rendered = 0;
	printf("h%dey %d @ %d.%d!\n",gui->btns, keycode, x, y);
	return (capture);
}

int	mouse_rel(int keycode, int x, int y, t_gui *gui)
{
	int	i;

	(void)(x * y);
	i = -1;
	while ((__u_int)++i < sizeof(BTNS) / sizeof(*BTNS))
		if (keycode == (int)BTNS[i])
			gui->btns &= ~(1 << i);
	return (0);
}

int	mouse_motion(int x, int y, t_gui *gui)
{
	static int	last[2];

	if (x != last[0])
		rotate(&gui->cam, (last[0] - x) / 4.0), gui->rendered = 0;
	if (y != last[1] && last[1])
		pitch(&gui->cam, (last[1] - y) / 4.0), gui->rendered = 0;
	last[0] = x;
	last[1] = y;
	if (mouse_press(0, 0, 0, gui))
	{
		x = loopbind(x, 30, SCRWIDTH - 30);
		// mlx_mouse_show(gui->mlx, gui->mlx->win_list);
		// printf("hey %d.%d!\n", x, y);
		if (x != bind(last[0], 20, SCRWIDTH - 20))
			XWarpPointer(gui->mlx->display, None, gui->mlx->win_list->window,
			0, 0, 0, 0, x, y), last[0] = x;
		// mlx_mouse_hide(gui->mlx, gui->mlx->win_list);
	}
	return (0);
}
