/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:33:13 by emis              #+#    #+#             */
/*   Updated: 2023/06/16 16:30:33 by emis             ###   ########.fr       */
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
	jump = XK_space,
	rot_left = XK_Left,
	rot_right = XK_Right,
}	t_kbind;

# define KEYS ((t_kbind[]){forth, back, left, right, jump, rot_left, rot_right})

typedef enum e_keypresses
{
	KP_forth,
	KP_back,
	KP_left,
	KP_right,
	KP_jump,
	KP_rot_left,
	KP_rot_right,
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
}	t_play;
 // plane = (t_vect){0, 0.66};

	// t_vect	dir;
typedef struct s_sprite
{
	t_vect	posi;
	t_img	img;
}	t_sprt;

typedef struct s_map
{
	int		width;
	int		height;
	int		**map;
	// char	**map;
	t_img	*textures;
	t_sprt	*sprites;
}	t_map;

typedef struct s_gui
{
	t_xvar	*mlx;
	t_map	*map;
	t_play	player;
	int		keys;
	_Bool	rendered;
}	t_gui;

/* RENDER */

int	render(t_gui *gui);

/* CONTROLS */

void	rotate(t_play	*play, int dir);
int		move(t_gui *gui);
int		key_press(int keycode, t_gui *gui);
int		key_rel(int keycode, t_gui *gui);

#endif