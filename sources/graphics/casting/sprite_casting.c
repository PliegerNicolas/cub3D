/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:26:04 by emis              #+#    #+#             */
/*   Updated: 2023/08/17 17:16:59 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

// translate sprite position to relative to camera
// transform sprite with the inverse camera matrix
// [ planeX   dirX ] -1                                     [ dirY      -dirX ]
// [               ]       =  1/(planeX*dirY-dirX*planeY) * [                 ]
// [ planeY   dirY ]                                        [ -planeY  planeX ]
static t_vect	transform(t_sprt *cur, t_play *play)
{
	t_vect	sprite;
	double	int_det;

	sprite = (t_vect){cur->posi.x - play->posi.x,
		cur->posi.y - play->posi.y};
	int_det = 1.0 / (play->plane.x * (play->dir.y * play->zoom)
			- (play->dir.x * play->zoom) * play->plane.y);
	return ((t_vect){
		int_det * ((play->dir.y * play->zoom) * sprite.x
			- (play->dir.x * play->zoom) * sprite.y),
		int_det * (-play->plane.y * sprite.x
			+ play->plane.x * sprite.y)});
}

typedef struct s_rc_sprite
{
	t_vect	transf;
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		cur_x;
	int		cur_y;
	int		start_y;
	int		end_x;
	int		end_y;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_rcs;

//calculate height of the sprite on screen
//using 'transformY' instead of the real distance prevents fisheye
//calculate lowest and highest pixel to fill in current stripe
//calculate width of the sprite
static void	compute_draw_bounds(t_sprt *cur, t_play *play, t_rcs *rc)
{
	rc->transf = transform(cur, play);
	rc->screen_x = (int)((SCRWIDTH / 2) * (1 + rc->transf.x / rc->transf.y));
	rc->sprite_height = abs((int)(SCRHEIGHT / (rc->transf.y))) / cur->scale.y;
	rc->start_y = bind(-rc->sprite_height / 2 + SCRHEIGHT / 2 + (play->pitch
				* SCRHEIGHT) + cur->offset / rc->transf.y, 0, SCRHEIGHT) - 1;
	rc->end_y = bind(rc->sprite_height / 2 + SCRHEIGHT / 2 + (play->pitch
				* SCRHEIGHT) + cur->offset / rc->transf.y, 0, SCRHEIGHT);
	rc->sprite_width = abs((int)(SCRHEIGHT / (rc->transf.y))) / cur->scale.x;
	rc->cur_x = bind(-rc->sprite_width / 2 + rc->screen_x, 0, SCRWIDTH) - 1;
	rc->end_x = bind(rc->sprite_width / 2 + rc->screen_x, 0, SCRWIDTH);
	rc->color = cur->alpha;
	if (play->dark)
		rc->color = bind(rc->color
				- (play->dark * (cur->dist + 1) / 8.0), 1, 255);
	rc->color = rc->color << 24;
}

//the conditions in the if are:
//1) it's in front of camera plane so you don't see things behind you
//2) it's on the screen (left)
//3) it's on the screen (right)
//4) z_buffer, with perpendicular distance
//256 and 128 factors to avoid floats
static void	draw_sprite(t_gui *gui, double z_buffer[SCRWIDTH], t_sprt *cur,
	t_rcs *rc)
{
	while (cur->alpha >= 0 && ++rc->cur_x < rc->end_x)
	{
		rc->tex_x = (int)((rc->cur_x - (-rc->sprite_width / 2 + rc->screen_x))
				* 256 * cur->frames[0]->width / rc->sprite_width) / 256;
		if (!(rc->transf.y > 0 && rc->cur_x > 0
				&& rc->cur_x < SCRWIDTH && rc->transf.y < z_buffer[rc->cur_x]))
			continue ;
		rc->cur_y = rc->start_y;
		while (++rc->cur_y < rc->end_y)
		{
			rc->tex_y = ((((rc->cur_y - (gui->cam.pitch * SCRHEIGHT)
								- cur->offset / rc->transf.y) * 256
							- SCRHEIGHT * 128 + rc->sprite_height * 128)
						* cur->frames[0]->height) / rc->sprite_height) / 256;
			rc->color = (rc->color & 0xFF000000);
			if (cur->frames[0]->width * rc->tex_y + rc->tex_x >= 0)
				rc->color |= pixget(cur->frames[cur->fcur],
						rc->tex_x, rc->tex_y) & 0xFFFFFF;
			if ((rc->color & 0x00FFFFFF) != 0)
				pixput(gui->buffer, rc->cur_x, rc->cur_y, rc->color);
		}
	}
}

void	sprite_cast(t_gui *gui, double z_buffer[SCRWIDTH])
{
	t_rcs	rc;
	t_sprt	*cur;

	set_dist_and_sort(&gui->textures, &gui->cam.posi);
	frame_shift(gui);
	cur = gui->textures.sprites;
	while (cur)
	{
		update_sprite(gui, cur);
		compute_draw_bounds(cur, &gui->cam, &rc);
		draw_sprite(gui, z_buffer, cur, &rc);
		cur = cur->next;
	}
}
