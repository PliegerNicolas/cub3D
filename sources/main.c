/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:42 by emis              #+#    #+#             */
/*   Updated: 2023/07/09 07:33:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "garbaj.h"
# include "graphics.h"
# include "parsing.h"

int	hello(void *lol)
{
	return printf("hey! %p\n", lol);
}

int	main(int ac, char **av)
{
	t_gui	gui;

	if (initialize(ac, av, &gui))
		return (1);
	//gui_init(&gui, ac, av);
	mlx_new_window(gui.mlx, SCRWIDTH, SCRHEIGHT, "cub3D my beloved");
	mlx_loop_hook(gui.mlx, &render, &gui);
	mlx_hook(gui.mlx->win_list, KeyPress, KeyPressMask, &key_press, &gui);
	mlx_hook(gui.mlx->win_list, KeyRelease, KeyReleaseMask, &key_rel, &gui);
	mlx_hook(gui.mlx->win_list, ButtonPress, ButtonPressMask, &mouse_press, &gui);
	mlx_hook(gui.mlx->win_list, ButtonRelease, ButtonReleaseMask, &mouse_rel, &gui);
	mlx_hook(gui.mlx->win_list, MotionNotify, PointerMotionMask, &mouse_motion, &gui);
	mlx_hook(gui.mlx->win_list, DestroyNotify, 0L, &mlx_loop_end, gui.mlx);
	mlx_hook(gui.mlx->win_list, Expose, 0L, hello, &gui);
	XWarpPointer(gui.mlx->display, None, gui.mlx->win_list->window,
		0, 0, 0, 0, SCRWIDTH / 2, SCRHEIGHT / 2);
	mlx_loop(gui.mlx);
	mlx_destroy_window(gui.mlx, gui.mlx->win_list);
	garbaj(NULL, NULL, 0);
	return (clear_parsing(&gui), 0);
}
