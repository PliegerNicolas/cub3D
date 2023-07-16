/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:33:13 by emis              #+#    #+#             */
/*   Updated: 2023/07/16 06:57:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

/* ************************************** */
/* * INCLUDES							* */
/* ************************************** */

# include <math.h>
# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include "garbaj.h"
# include "parsing.h"

# define SCRWIDTH 1200
# define SCRHEIGHT 1000

/* ************************************** */
/* * ENUMERATORS						* */
/* ************************************** */

typedef enum e_keybinds
{
	forth = XK_w,
	back = XK_s,
	left = XK_a,
	right = XK_d,
	sprint = XK_Shift_L,
	rot_left = XK_Left,
	rot_right = XK_Right,
	rot_up = XK_Up,
	rot_down = XK_Down,
	zoom_in = XK_KP_Add,
	zoom_out = XK_KP_Subtract,
	interactkey = XK_e,
}	t_kbind;

typedef enum e_keypresses
{
	KP_forth,
	KP_back,
	KP_left,
	KP_right,
	KP_sprint,
	KP_rot_left,
	KP_rot_right,
	KP_rot_up,
	KP_rot_down,
	KP_zoom_in,
	KP_zoom_out,
	KP_interact,
}	t_kprs;

typedef enum e_btnpresses
{
	left_click = 1,
	mid_click,
	right_click,
	scroll_up,
	scroll_down,
}	t_bprs;

typedef enum e_render_level
{
	BASICWALLS,
	TEXTUWALLS,
	SPRITES,
	FLOORCEIL
}	t_rndr;

typedef enum e_type
{
	STATIONARY,
	MOVING,
	ALIVE,
	DEAD
}	t_type;

enum e_rates
{
	RATE_MOVE,
	RATE_MOB,
	RATE_ITEM,
	RATE_DOOR,
};

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

/* Maths */

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef struct s_ray_caster
{
	int		x;
	int		y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	t_vect	ray_dir;
	t_vect	side_dist;
	t_vect	delta_dist;
	double	perp_wall_dist;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_rc;

/* Game data */

typedef struct s_player
{
	t_rndr	rndr;
	t_vect	posi;
	t_vect	dir;
	t_vect	plane;
	int		pitch;
	double	zoom;
	double	zoom_rate;
	t_vect	speed;
	t_vect	speed_target;
	double	sprint_multiplicator;
	t_vect	rot_speed;
	t_vect	rot_speed_target;
	t_vect	accel_rate;
	t_vect	rot_accel_rate;
	t_vect	hit_box;
}	t_play;

typedef struct s_sprite
{
	t_type	type;
	_Bool	solid;
	t_vect	posi;
	int		alpha;
	int		fcur;
	int		fnum;
	t_img	**frames;
}	t_sprt;

# define DOOR_OPEN 42
# define DOOR_CLOSED 43

typedef struct s_textures
{
	int		width;
	int		height;
	int		floor_color;
	int		ceil_color;
	t_img	**floorceil;
	int		arrsize;
	t_img	**walls;
	t_img	**doors;
	int		spnb;
	int		*sporder;
	double	*spdist;
	t_sprt	*sprites;
}	t_tex;

typedef struct s_map
{
	size_t	width;
	size_t	height;
	int		**map;
}	t_map;

typedef struct s_gui
{
	t_xvar	*mlx;
	void	*win;
	t_img	*buffer;
	t_map	map;
	t_tex	textures;
	t_play	cam;
	int		keys;
	int		btns;
	_Bool	rendered;
}	t_gui;

/* ************************************** */
/* * GLOBAL VAR							* */
/* ************************************** */

/* ************************************** */
/* * MACRO								* */
/* ************************************** */

# define DOOR 42

/* ************************************** */
/* * FUNCTIONS							* */
/* ************************************** */

/* RENDER */

int		render(t_gui *gui);

/* IMAGE */

int		pixget(t_img *img, int x, int y);
void	pixput(t_img *img, int x, int y, int color);
void	erase(t_img *img);
void	imgput(t_img *dest, int x, int y, t_img *img);

/* CONTROLS */

void	key_render(t_gui *gui);
void	move(t_gui *gui);
void	zoom(t_play	*player, double dir);
void	pitch(t_play *player, double dir);
void	rotate(t_play *player, double dir);

//utils

void	check_and_move(t_map map, t_vect *posi, t_vect dxdy, double magn);
void	update_speed(double *current_speed, double target_speed,
			double acceleration_rate);
void	set_keys_arr(t_kbind *keys);
void	set_btns_arr(t_bprs *mouse_btns);

/* EVENTS */

int		key_press(int keycode, t_gui *gui);
int		key_rel(int keycode, t_gui *gui);
int		mouse_press(int keycode, int x, int y, t_gui *gui);
int		mouse_rel(int keycode, int x, int y, t_gui *gui);
int		mouse_motion(int x, int y, t_gui *gui);

/* TEXTURES */

t_img	*load_texture(t_gui *gui, char *path);
void	load_texture_arr(t_gui *gui, t_img ***where, char *path, int size);

/* MINIMATH */

int		bind(int val, int min, int max);
int		loop_bind(int val, int min, int max);
double	inv_safe(double x);

/* VECTOR */

double	magnitude(t_vect v);
double	angle(t_vect v1, t_vect v2);
t_vect	delta(t_vect from, t_vect to);

/* FLOOR CASTING */

void	floor_cast(t_gui *gui);

/* WALL CASTING */

void	wall_cast(t_gui *gui, double z_buffer[SCRWIDTH]);
void	wall_color(t_gui *gui, t_rc *rc);
void	wall_texture(t_gui *gui, t_rc *rc);

/* FRAMERATE */

int		nextframe(int frnb);

/* SPRITE CASTING */

void	sprite_cast(t_gui *gui, double ZBuffer[SCRWIDTH]);
// void	sort_sprites(t_tex *tex, t_vect *from);

/* MINIMAP */

void	minimap(t_gui *gui);

/* WEAPON */

void	weapon(t_gui *gui);

/* INTERACT */

int	interact(t_gui *gui);

/* ************************************** */
/* * TEMP, NEEDED FOR PARSING			* */
/* ************************************** */

bool	initialize(int argc, char **argv, t_gui *gui);
bool	parse_cub_file(t_gui *gui, int fd);
bool	act_on_type_identifier(t_gui *gui, char *line, t_type_id ti);

/* set_texture.c */

bool	set_texture(t_gui *gui, char *line, t_type_id ti);
bool	set_color(t_gui *gui, char *line, t_type_id ti);

/* free.c */

void	clear_parsing(t_gui *gui);
void	free_str_arr(char **arr);

/* convert_map_ctrl_to_int_arr.c */

bool	convert_map_ctrl_to_int_arr(t_gui *gui, t_map_ctrl *map_ctrl);

/* is_map_closed.c */

bool	is_map_closed(const t_gui *gui);

/* set_player.c */

bool	set_player(t_gui *gui);

/* set_sprites.c */

bool	set_sprites(t_gui *gui);

/* set_mobs.c */

bool	set_mobs(t_gui *gui);

#endif
