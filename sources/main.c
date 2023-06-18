/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:42 by emis              #+#    #+#             */
/*   Updated: 2023/06/18 19:22:26 by emis             ###   ########.fr       */
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
#define SPAWN 3
#if SPAWN == 0 // NORTH
	gui.player.dir = (t_vect){-1, 0};
	gui.player.plane = (t_vect){0, 0.66};
#elif SPAWN == 1 // SOUTH
	gui.player.dir = (t_vect){1, 0};
	gui.player.plane = (t_vect){0, -0.66};
#elif SPAWN == 2 // WEST
	gui.player.dir = (t_vect){0, -1};
	gui.player.plane = (t_vect){-0.66, 0};
#else // EAST
	gui.player.dir = (t_vect){0, 1};
	gui.player.plane = (t_vect){0.66, 0};
#endif
	gui.player.zoom = 1;
	gui.player.speed = 1;
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
	gui.keys = 0;
	gui.rendered = 0;
	gui.textures.height = gui.textures.width = 32; //64
	// gui.textures.textures = load_texture(&gui, "textures/shrek.xpm");
	gui.textures.ceil_col = (200 << 0) | (50 << 8) | (50 << 16);
	gui.textures.floor_col = (50 << 0) | (100 << 8) | (50 << 16);
	gui.textures.arrsize = 4;
	gui.textures.walls = NULL;
	load_texture_arr(&gui, &gui.textures.walls, "textures/solong/40.xpm", 4);
	load_texture_arr(&gui, &gui.textures.walls, "textures/solong/41.xpm", 4);
	load_texture_arr(&gui, &gui.textures.walls, "textures/solong/42.xpm", 4);
	load_texture_arr(&gui, &gui.textures.walls, "textures/solong/43.xpm", 4);
	gui.buffer = mlx_new_image(gui.mlx, SCRWIDTH, SCRHEIGHT);
	mkorbrk(gui.buffer, mlximgwrap, !gui.buffer, 1);
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
