/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:42 by emis              #+#    #+#             */
/*   Updated: 2023/07/18 03:58:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbaj.h"
#include "graphics.h"
#include "parsing.h"

static void	initialize_mouse(t_gui *gui)
{
	mlx_mouse_move(gui->mlx, gui->win, SCRWIDTH / 2, SCRHEIGHT / 2);
}

int	main(int ac, char **av)
{
	t_gui	gui;

	if (initialize(ac, av, &gui))
		return (1);
	gui.win = mlx_new_window(gui.mlx, SCRWIDTH, SCRHEIGHT, "cub3D my beloved");
	initialize_mouse(&gui);
	mlx_loop_hook(gui.mlx, &render, &gui);
	mlx_hook(gui.win, KeyPress, KeyPressMask, &key_press, &gui);
	mlx_hook(gui.win, KeyRelease, KeyReleaseMask, &key_rel, &gui);
	mlx_hook(gui.win, ButtonPress, ButtonPressMask, &mouse_press, &gui);
	mlx_hook(gui.win, ButtonRelease, ButtonReleaseMask, &mouse_rel, &gui);
	mlx_hook(gui.win, MotionNotify, PointerMotionMask, &mouse_motion, &gui);
	mlx_hook(gui.win, DestroyNotify, 0L, &mlx_loop_end, gui.mlx);
	mlx_loop(gui.mlx);
	mlx_destroy_window(gui.mlx, gui.mlx->win_list);
	garbaj(NULL, NULL, 0);
	return (clear_parsing(&gui), 0);
}
