/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:42 by emis              #+#    #+#             */
/*   Updated: 2023/06/16 15:16:07 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/garbaj.h"
# include "../includes/graphics.h"
# include "../includes/parsing.h"

//singletons aka global variables ?
// t_gui	*gui(void)
// {
// 	static t_gui	*gui;

// 	if (!gui)
// 	{
// 		gui = trymalloc(sizeof(t_gui), 0);
// 		gui->mlx = mlx_init();
// 		mkorbrk(gui->mlx, mlxwrap, !gui->mlx, 0);
// 		// gui->player = trymalloc(sizeof(t_play), 0);
// 		gui->player.posi = (t_vect){22, 12};
// 		gui->player.dir = (t_vect){0, 0};
// 		gui->player.plane = (t_vect){0, 0.66};

// 	}
// 	return (gui);
// }

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	hello(void *lol)
{
	return printf("hey! %p\n", lol);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_gui	gui;
	gui.mlx = mlx_init();
	mkorbrk(gui.mlx, mlxwrap, !gui.mlx, 0);
	gui.player.posi = (t_vect){22, 12};
	gui.player.dir = (t_vect){1, 1};
	gui.player.plane = (t_vect){0, 0.66};
	gui.map = trymalloc(sizeof(t_map), 0);
	gui.map->width = mapWidth;
	gui.map->height = mapHeight;
	gui.map->map = trymalloc(sizeof(int *) * gui.map->width, 0);
	for(int x = 0; x < gui.map->width; x++)
	{
		gui.map->map[x] = trymalloc(sizeof(int) * gui.map->height, 0);
		for(int y = 0; y < gui.map->height; y++)
			gui.map->map[x][y] = worldMap[x][y];
	}
	// union Point p = {3.14f, 0.0f, 1.2f};
	// p.xyz.x = 1.1f;
	mlx_new_window(gui.mlx, SCRWIDTH, SCRHEIGHT, "TITLE");
	mlx_loop_hook(gui.mlx, &render, &gui);
	mlx_hook(gui.mlx->win_list, KeyPress, KeyPressMask, &key_press, &gui);
	mlx_hook(gui.mlx->win_list, KeyRelease, KeyReleaseMask, &key_rel, &gui);
	mlx_hook(gui.mlx->win_list, DestroyNotify, 0L, &mlx_loop_end, gui.mlx);
	mlx_hook(gui.mlx->win_list, Expose, 0L, hello, &gui);
	mlx_loop(gui.mlx);
	mlx_destroy_window(gui.mlx, gui.mlx->win_list);
	garbaj(NULL, NULL, 0);
	return (0);
}
