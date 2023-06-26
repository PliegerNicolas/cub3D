/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:33:13 by emis              #+#    #+#             */
/*   Updated: 2023/06/26 07:13:32 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <math.h>
# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include "garbaj.h"
# include "parsing.h"

#define SCRWIDTH 1200
#define SCRHEIGHT 1000

typedef enum e_keybinds
{
	forth = XK_w,
	back = XK_s,
	left = XK_a,
	right = XK_d,
	sprint = XK_Shift_L,
	rot_left = XK_Left,
	rot_right = XK_Right,
	zoom_in = XK_Up,
	zoom_out = XK_Down,
}	t_kbind;

# define KEYS ((t_kbind[]){forth, back, left, right, sprint, rot_left, rot_right, zoom_in, zoom_out})

typedef enum e_keypresses
{
	KP_forth,
	KP_back,
	KP_left,
	KP_right,
	KP_sprint,
	KP_rot_left,
	KP_rot_right,
	KP_zoom_in,
	KP_zoom_out,
}	t_kprs;

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef struct s_player
{
	enum e_render_level
	{
		BASICWALLS,
		TEXTUWALLS,
		SPRITES,
		FLOORCEIL
	}		rndr;
	t_vect	posi;
	t_vect	dir;
	t_vect	plane;
	int		pitch;
	double	zoom;
	double	speed;
}	t_play;
 // plane = (t_vect){0, 0.66};

typedef struct s_sprite
{
	enum e_type
	{
		STATIONARY,
		MOVING,
		ALIVE,
		DEAD
	}		type;
	_Bool	solid;
	t_vect	posi;
	int		alpha;
	int		fcur;
	int		fnum;
	t_img	**frames;
}	t_sprt;

typedef struct s_textures
{
	int		width;
	int		height;
	int		floor_col;
	int		ceil_col;
	t_img	**floorceil;
	int		arrsize;
	t_img	**walls;
	int		spnb;
	int		*sporder;
	double	*spdist;
	t_sprt	*sprites;
}	t_tex;

typedef struct s_map
{
	int		width;
	int		height;
	int		**map;
	// char	**map;
}	t_map;

typedef struct s_gui
{
	t_xvar	*mlx;
	t_img	*buffer;
	t_map	*map;
	t_tex	textures;
	t_play	cam;
	int		keys;
	_Bool	rendered;
}	t_gui;

/* RENDER */

int		render(t_gui *gui);

/* IMAGE */

int		pixget(t_img *img, int x, int y);
void	pixput(t_img *img, int x, int y, int color);
void	erase(t_img *img);

/* CONTROLS */

void	zoom(t_play	*play, int dir);
void	rotate(t_play	*play, int dir);
void	check_and_move(t_map *map, t_vect *posi, t_vect dxdy, double magn);
int		move(t_gui *gui);
int		key_press(int keycode, t_gui *gui);
int		key_rel(int keycode, t_gui *gui);

/* TEXTURES */

t_img	*load_texture(t_gui *gui, char *path);
void	load_texture_arr(t_gui *gui, t_img ***where, char *path, int size);

/* MINIMATH */

int		bind(int val, int min, int max);
double	invSafe(double x);
t_vect	delta(t_vect from, t_vect to);

/* FLOOR CASTING */

void	floor_cast(t_gui *gui);

/* WALL CASTING */

void	wall_cast(t_gui *gui, double ZBuffer[SCRWIDTH]);

/* SPRITE CASTING */

void	sprite_cast(t_gui *gui, double ZBuffer[SCRWIDTH]);
// void	sort_sprites(t_tex *tex, t_vect *from);

/* MINIMAP */

void	minimap(t_gui *gui);







/* ************************************** */
/* * TEMP, NEEDED FOR PARSING			* */
/* ************************************** */

bool	initialize(int argc, char **argv, t_gui *gui);
bool	parse_cub_file(t_gui *gui, int fd);

#endif
