/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:33:13 by emis              #+#    #+#             */
/*   Updated: 2023/08/16 17:02:57 by nplieger         ###   ########.fr       */
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

# define SCRWIDTH 1280
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
	mapkey = XK_Tab,
	space = XK_space,
	statistics = XK_F3,
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
	KP_map,
	KP_space,
	KP_statistics,
}	t_kprs;

typedef enum e_btnpresses
{
	left_click = 1,
	mid_click,
	right_click,
	scroll_up,
	scroll_down,
}	t_bprs;

typedef enum	e_rndr_toggle
{
	TOGGLE = 0,
	OFF = 1,
	ON = 2,
}	t_rndr_toggle;

typedef enum e_render_level
{
	TEXTUWALLS = 1,
	FLOORCEIL = 2,
	SPRITES = 4,
	MINIMAP = 8,
	MINIMAP_CIRCULAR = 16,
	MINIMAP_FOCUS = 32,
	STATISTICS = 64,
}	t_rndr;

typedef enum e_type
{
	STATIONARY,
	COLLECTIBLE,
	ALIVE,
	DEAD
}	t_type;

enum e_rates
{
	RATE_MOVE,
	RATE_MOB,
	RATE_ITEM,
	RATE_DOOR,
	RATE_SPRINT,
	RATE_HEAL,
	RATE_ARMOR_UP,
	RATE_SHOOT,
	RATE_NB
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

# define NB_MOBTYPE 5
# define NB_OBJTYPE 5

typedef enum e_stat_field
{
	HP,
	STA,
	ARM,
	AMMO,
	XP,
	LVL,
	SIZE
}	t_fld;

typedef struct projectile
{
	t_vect	posi;
	t_vect	direction;
	bool	status;
}	t_prj;

typedef struct s_stats
{
	int	get[SIZE];
	int	max[SIZE];
}	t_stat;

typedef struct s_player
{
	t_stat	stat;
	int		rndr;
	t_vect	posi;
	t_vect	dir;
	t_vect	plane;
	double	pitch;
	int		dark;
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

typedef struct s_sprite	t_sprt;

typedef struct s_sprite
{
	t_type	type;
	t_fld	stat;
	int		amount;
	bool	solid;
	t_vect	posi;
	int		alpha;
	int		fcur;
	int		fnum;
	t_img	**frames;
	t_vect	scale;
	double	offset;
	double	dist;
	t_sprt	*next;
}	t_sprt;

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
	t_img	**spframes[SIZE + NB_OBJTYPE + NB_MOBTYPE];
	size_t	spfrsizes[SIZE + NB_OBJTYPE + NB_MOBTYPE];
	t_img	*weapon;
	int		spnb;
	t_sprt	*sprites;
}	t_tex;
	// int		*sporder;
	// double	*spdist;

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
	bool	rendered;
}	t_gui;

/* ************************************** */
/* * GLOBAL VAR							* */
/* ************************************** */

/* ************************************** */
/* * MACRO								* */
/* ************************************** */

# define E_SPTEXTID "Wrong/missing sprite identifier in cub file.\n"
# define E_SPTEXTNB "Wrong/missing frame count in cub file.\n"

# define DOOR_OPEN 42
# define DOOR_CLOSED 43

// weapon

# define WALK_AMPLITUDE 8
# define WALK_FREQUENCY 30
# define PROJECTILE_SPEED 0.20
# define MAX_PROJECTILES 25

// colors

# define DARK 0x20
# define VERY_DARK 0x32
# define DARKNESS 0x50

# define MAPBLACK 0x010101
# define MAPWHITE 0xFFFFFF
# define MAPGREY 0xAAAAAA
# define MAPRED 0xFF0000
# define MAPGREEN 0x00FF00
# define MAPBLUE 0x4fa8e3
# define MAPMAG 0xFF11FF
# define MAPMAGF 0xAAFF44FF
# define MAPYEL 0xFFFF00

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* ************************************** */
/* * FUNCTIONS							* */
/* ************************************** */

/* RENDER */

int		render(t_gui *gui);

/* IMAGE */

int		pixget(t_img *img, int x, int y);
int		color_mixer(int from, int to, int alpha);
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
void	update_rotation_speed(double *current_speed, double target_speed,
			double acceleration_rate, double direction);
int		get_keypress_index(int keycode);
int		get_mousepress_index(int keycode);
void	initialize_mouse_motion(t_gui *gui, int last[2]);

void	act_on_sprint(t_gui *gui);
void	act_on_move(t_gui *gui);
void	act_on_camera_rotation(t_gui *gui, t_play *p);
void	act_on_zoom(t_gui *gui);
void	act_on_toggles(t_gui *gui);

/* EVENTS */

int		key_press(int keycode, t_gui *gui);
int		key_rel(int keycode, t_gui *gui);
int		mouse_press(int keycode, int x, int y, t_gui *gui);
int		mouse_rel(int keycode, int x, int y, t_gui *gui);
int		mouse_motion(int x, int y, t_gui *gui);

/* TEXTURES */

t_img	*load_texture(t_gui *gui, char *path);
bool	load_texture_arr(t_gui *gui, t_img ***where, char *path, int size);

/* MINIMATH */

int		bind(int val, int min, int max);
int		loop_bind(int val, int min, int max);
double	inv_safe(double x);

/* VECTOR */

double	magnitude(t_vect v);
double	angle(t_vect v1, t_vect v2);
t_vect	delta(t_vect from, t_vect to);
t_vect	scale(t_vect v, double scalar);
t_vect	perp(t_vect v);

/* VECTOR2 */

t_vect	v_add(t_vect v, t_vect w);
t_vect	v_sub(t_vect v, t_vect w);
t_vect	v_mul(t_vect v, t_vect w);
t_vect	v_div(t_vect v, t_vect w);
t_vect	v_rot(t_vect v, t_vect w);

/* FLOOR CASTING */

void	floor_cast(t_gui *gui);

/* WALL CASTING */

void	wall_cast(t_gui *gui, double z_buffer[SCRWIDTH]);
void	wall_color(t_gui *gui, t_rc *rc);
void	wall_texture(t_gui *gui, t_rc *rc);

/* FRAMERATE */

int		nextframe(enum e_rates frnb);

/* SPRITE CASTING */

void	sprite_cast(t_gui *gui, double ZBuffer[SCRWIDTH]);
// void	sort_sprites(t_tex *tex, t_vect *from);

/* DRAW */

void	dot(t_img *img, int px, int py, int color);
void	tri(t_img *img, t_vect at, t_vect dir, int color);

/* MINIMAP */

int		minimap(t_gui *gui, t_vect where, size_t s, bool c);
int		fullmap(t_gui *gui, t_vect where);

/* HUD */

void	hud(t_gui *gui);

/* WEAPON */

void	weapon(t_gui *gui);
int		calculate_next_walk_frame(t_gui *gui, int frame);
void	set_weapon_position(t_gui *gui, int *x, int *y, int frame);

bool	is_projectile_obstructed(t_gui *gui, t_prj *projectile);
bool	move_projectile(t_gui *gui, t_prj *projectile);

bool	is_out_of_bounds(t_gui *gui, int cell_x, int cell_y);
bool	wall_collision(t_gui *gui, int cell_x, int cell_y);
bool	is_target_position_found(t_vect target_position, int cell_x,
			int cell_y);
bool	sprite_collision(t_gui *gui, int cell_x, int cell_y);

void	draw_projectile(t_gui *gui, int x, int y, double distance);
void	draw_projectile_impact(t_gui *gui, int x, int y, double distance);
void	draw_crosshair(t_gui *gui, int color);

void	initialize_projectile(t_play *player, t_prj *projectile);
void	clear_projectile(t_prj *projectile);

/* INTERACT */

bool	check_press(bool press, size_t i);
int		interact(t_gui *gui);

/* STATS */

void	gain_xp(t_gui *gui, t_sprt *ded);
void	regen(t_gui *gui, t_fld fld, int amount, enum e_rates rate);

/* BITMASK */

bool	is_mask_set(int *mask, t_rndr option);
void	toggle_mask(int *mask, t_rndr option, t_rndr_toggle status);
void	select_map_type(int *mask);
void	change_render_type(int *mask);

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

t_sprt	*add_sprite(t_sprt **list, t_sprt *sprite);
bool	set_mob_obj_frames(t_gui *gui, size_t which, char **args, int num);
bool	set_frames(t_gui *gui, size_t which, char *path, int num);

/* set_mobs.c */

t_sprt	*add_mob(t_gui *gui, t_vect posi, size_t which);
t_sprt	*add_pack(t_gui *gui, t_vect posi, size_t which);
bool	set_mobs(t_gui *gui);

/* set_weapon.c */

bool	set_weapon(t_gui *gui, char *line);

#endif
