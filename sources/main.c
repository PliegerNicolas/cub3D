/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:18:42 by emis              #+#    #+#             */
/*   Updated: 2023/07/02 06:14:26 by nicolas          ###   ########.fr       */
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
// 		// gui->cam = trymalloc(sizeof(t_play), 0);
// 		gui->cam.posi = (t_vect){22, 12};
// 		gui->cam.dir = (t_vect){0, 0};
// 		gui->cam.plane = (t_vect){0, 0.66};

// 	}
// 	return (gui);
// }

/*
#define mapWidth 24
#define mapHeight 24

typedef enum e_map_symbols
{
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	FLOOR = '0',
	WALL = '1'
}	t_sym;

# define SYMBOLS ((t_sym[]){NORTH, SOUTH, EAST, WEST, FLOOR, WALL})
# define SYMSTR ("NSEW01") // to check map use strchr on this string ?

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
// 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
// 	{1,4,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
*/
int	hello(void *lol)
{
	return printf("hey! %p\n", lol);
}

/*
void	map_init(t_map *map, char *filename)
{
	(void)filename;
	map->width = mapWidth;
	map->height = mapHeight;
	map->map = trymalloc(sizeof(int *) * map->width, 0);
	for(size_t x = 0; x < map->width; x++)
	{
		map->map[x] = trymalloc(sizeof(int) * map->height, 0);
		for(size_t y = 0; y < map->height; y++)
			map->map[x][y] = worldMap[x][y];
	}
}

void	player_init(t_play *player, t_vect posi, int orient)
{
	player->posi = posi;
	player->pitch = 0;//100;
	player->zoom = 1;
	player->speed = 1;
	player->rndr = FLOORCEIL;
	if (orient == NORTH)
	{
		player->dir = (t_vect){-1, 0};
		player->plane = (t_vect){0, 0.66};
	}
	else if (orient == SOUTH)
	{
		player->dir = (t_vect){1, 0};
		player->plane = (t_vect){0, -0.66};
	}
	else if (orient == EAST)
	{
		player->dir = (t_vect){0, 1};
		player->plane = (t_vect){0.66, 0};
	}
	else
	{
		player->dir = (t_vect){0, -1};
		player->plane = (t_vect){-0.66, 0};
	}
}

void	gui_init(t_gui *gui, int ac, char **av)
{
	if (!ac) // ac != 2
		exit(garbaj(NULL, NULL, 0) + 1);
	gui->mlx = mlx_init();
	mkorbrk(gui->mlx, mlxwrap, !gui->mlx, 0);
	player_init(&gui->cam, (t_vect){22, 12}, 'N');
	//gui->map = trymalloc(sizeof(t_map), 0);
	map_init(&gui->map, av[1]);
	gui->keys = 0;
	gui->btns = 0;
	gui->rendered = 0;
	gui->buffer = mlx_new_image(gui->mlx, SCRWIDTH, SCRHEIGHT);
	mkorbrk(gui->buffer, mlximgwrap, !gui->buffer, 1);

	gui->textures.height = gui->textures.width = 32; //64
	// gui->textures.textures = load_texture(&gui, "textures/shrek.xpm");
	gui->textures.ceil_color = (200 << 0) | (50 << 8) | (50 << 16);
	gui->textures.floor_color = (50 << 0) | (100 << 8) | (50 << 16);
	gui->textures.floorceil = NULL;
	load_texture_arr(gui, &gui->textures.floorceil, "textures/solong/00.xpm", 4);
	load_texture_arr(gui, &gui->textures.floorceil, "textures/solong/10.xpm", 4);
	gui->textures.arrsize = 4;
	gui->textures.walls = NULL;
	load_texture_arr(gui, &gui->textures.walls, "textures/solong/00.xpm", 4);
	load_texture_arr(gui, &gui->textures.walls, "textures/solong/10.xpm", 4);
	load_texture_arr(gui, &gui->textures.walls, "textures/solong/20.xpm", 4);
	load_texture_arr(gui, &gui->textures.walls, "textures/solong/30.xpm", 4);
#define SPRITES 2
	gui->textures.spnb = SPRITES;
	gui->textures.sporder = trymalloc(sizeof(int) * SPRITES, 1);
	gui->textures.sporder[0] = 0;
	gui->textures.sporder[1] = 1;
	gui->textures.spdist = trymalloc(sizeof(double) * SPRITES, 1);
	gui->textures.spdist[0] = 0;
	gui->textures.spdist[1] = 0;
	gui->textures.sprites = trymalloc(sizeof(t_sprt) * SPRITES, 1);

	gui->textures.sprites[0].posi = (t_vect){10, 10};
	gui->textures.sprites[0].solid = 1;
	gui->textures.sprites[0].type = STATIONARY;
	gui->textures.sprites[0].fcur = 4;
	gui->textures.sprites[0].fnum = 8;
	load_texture_arr(gui, &gui->textures.sprites[0].frames, "textures/solong/slime0.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[0].frames, "textures/solong/slime1.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[0].frames, "textures/solong/slime2.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[0].frames, "textures/solong/slime3.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[0].frames, "textures/solong/slime4.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[0].frames, "textures/solong/slime5.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[0].frames, "textures/solong/slime6.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[0].frames, "textures/solong/slime7.xpm", 8);

	gui->textures.sprites[1].posi = (t_vect){9, 9};
	gui->textures.sprites[1].solid = 1;
	gui->textures.sprites[1].type = ALIVE;
	gui->textures.sprites[1].fcur = 0;
	gui->textures.sprites[1].fnum = 8;
	load_texture_arr(gui, &gui->textures.sprites[1].frames, "textures/solong/slime0.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[1].frames, "textures/solong/slime1.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[1].frames, "textures/solong/slime2.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[1].frames, "textures/solong/slime3.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[1].frames, "textures/solong/slime4.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[1].frames, "textures/solong/slime5.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[1].frames, "textures/solong/slime6.xpm", 8);
	load_texture_arr(gui, &gui->textures.sprites[1].frames, "textures/solong/slime7.xpm", 8);

}
*/

int	main(int ac, char **av)
{
	t_gui	gui;

	if (initialize(ac, av, &gui))
		return (1);
	//return (clear_parsing(&gui), 0);
	// test
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
	mlx_loop(gui.mlx);
	mlx_destroy_window(gui.mlx, gui.mlx->win_list);
	garbaj(NULL, NULL, 0);
	return (clear_parsing(&gui), 0);
}
