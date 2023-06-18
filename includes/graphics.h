/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:33:13 by emis              #+#    #+#             */
/*   Updated: 2023/06/18 19:18:44 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <math.h>
# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include "garbaj.h"

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
	t_vect	posi;
	t_vect	dir;
	t_vect	plane;
	double	zoom;
	double	speed;
}	t_play;
 // plane = (t_vect){0, 0.66};

	// t_vect	dir;
typedef struct s_sprite
{
	t_vect	posi;
	t_img	img;
}	t_sprt;

typedef struct s_textures
{
	int		width;
	int		height;
	t_img	*textures;
	int		arrsize;
	t_img	**walls;
	int		floor_col;
	int		ceil_col;
}	t_tex;

typedef struct s_map
{
	int		width;
	int		height;
	int		**map;
	// char	**map;
	t_sprt	*sprites;
}	t_map;

typedef struct s_gui
{
	t_xvar	*mlx;
	t_img	*buffer;
	t_map	*map;
	t_tex	textures;
	t_play	player;
	int		keys;
	_Bool	rendered;
}	t_gui;

/* RENDER */

int	render(t_gui *gui);

/* CONTROLS */

void	zoom(t_play	*play, int dir);
void	rotate(t_play	*play, int dir);
int		move(t_gui *gui);
int		key_press(int keycode, t_gui *gui);
int		key_rel(int keycode, t_gui *gui);

/* TEXTURES */

t_img	*load_texture(t_gui *gui, char *path);
void	load_texture_arr(t_gui *gui, t_img ***where, char *path, int size);

#endif