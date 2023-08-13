/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:26:04 by emis              #+#    #+#             */
/*   Updated: 2023/08/13 12:31:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	sort_lst(t_sprt **lst)
{
	t_sprt	*top;
	t_sprt	*sp;
	t_sprt	*old;

	top = *lst;
	sp = top;
	while (sp->next)
	{
		if (sp->dist < sp->next->dist)
		{
			if (sp == top)
			{
				top = top->next;
				sp->next = top->next;
				top->next = sp;
			}
			else
			{
				old->next = sp->next;
				sp->next = old->next->next;
				old->next->next = sp;
			}
			sp = top;
		}
		old = sp;
		sp = sp->next;
	}
	*lst = top;
}

static void	set_dist_and_sort(t_tex *tex, t_vect *from)
{
	t_sprt	*sp;
	double	last;
	bool	sort;

	sp = tex->sprites;
	last = -1;
	sort = 0;
	while (sp)
	{
		sp->dist = ((from->x - sp->posi.x)
			* (from->x - sp->posi.x)
			+ (from->y - sp->posi.y)
			* (from->y - sp->posi.y)); //sqrt not taken, unneeded
		if (last > -1 && sp->dist < last)
			sort = 1;
		last = sp->dist;
		sp = sp->next;
	}
	if (sort)
		sort_lst(&tex->sprites);
}

// translate sprite position to relative to camera
// transform sprite with the inverse camera matrix
// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
// [ planeY   dirY ]                                          [ -planeY  planeX ]
t_vect	transform(t_sprt *cur, t_play *play)
{
	t_vect	sprite;
	double	invDet;

	sprite = (t_vect){cur->posi.x - play->posi.x,
		cur->posi.y - play->posi.y};
	invDet = 1.0 / (play->plane.x * (play->dir.y * play->zoom)
		- (play->dir.x * play->zoom) * play->plane.y);
	return ((t_vect){
		invDet * ((play->dir.y * play->zoom) * sprite.x
		- (play->dir.x * play->zoom) * sprite.y),
		invDet * (-play->plane.y * sprite.x
		+ play->plane.x * sprite.y)});
}

void	frame_shift(t_tex *tex)
{
	t_sprt	*sp;
	t_sprt	*old;

	if (!nextframe(RATE_MOB))
		return;
	sp = tex->sprites;
	while (sp)
	{
		if (sp->type != DEAD)
			sp->fcur = (sp->fcur + 1) % sp->fnum;
		else if (sp->type == DEAD && sp->alpha < 0)
		{
			if (sp == tex->sprites)
				tex->sprites = sp->next;
			else
				old->next = sp->next;
			garbaj(sp, NULL, -1);
			if (!--tex->spnb)
				tex->sprites = NULL;
		}
		old = sp;
		sp = sp->next;
	}
}

void	sprite_cast(t_gui *gui, double ZBuffer[SCRWIDTH])
{
	t_vect	transf;
	t_sprt	*cur;

	set_dist_and_sort(&gui->textures, &gui->cam.posi);
	frame_shift(&gui->textures);

	cur = gui->textures.sprites;

	//after sorting the sprites, do the projection and draw them
	// for(int i = 0; i < gui->textures.spnb; i++)
	while (cur)
	{
		if (cur->type == ALIVE
			&& cur->dist > .3)
			check_and_move(gui->map, &cur->posi, 
			delta(cur->posi, gui->cam.posi), 0.025);
		else if (cur->type == DEAD)
			cur->alpha -= 7 * (cur->alpha > 0);
		if (cur->alpha < 0)
		{
			cur = cur->next;
			continue;
			// delete sprite
		}
		transf = transform(cur, &gui->cam);

		int spriteScreenX = (int)((SCRWIDTH / 2) * (1 + transf.x / transf.y));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(SCRHEIGHT / (transf.y))); //using 'transformY' instead of the real distance prevents fisheye

		// int pitch = 100;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = bind(-spriteHeight / 2 + SCRHEIGHT / 2 + (gui->cam.pitch * SCRHEIGHT), 0, SCRHEIGHT);
		// if (drawStartY < 0)
		// 	drawStartY = 0;
		int drawEndY = bind(spriteHeight / 2 + SCRHEIGHT / 2 + (gui->cam.pitch * SCRHEIGHT), 0, SCRHEIGHT);
		// if (drawEndY >= SCRHEIGHT)
		// 	drawEndY = SCRHEIGHT - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(SCRHEIGHT / (transf.y)));
		int drawStartX = bind(-spriteWidth / 2 + spriteScreenX, 0, SCRWIDTH);
		// if (drawStartX < 0)
		// 	drawStartX = 0;
		int drawEndX = bind(spriteWidth / 2 + spriteScreenX, 0, SCRWIDTH);
		// if (drawEndX >= SCRWIDTH)
		// 	drawEndX = SCRWIDTH - 1;
		// int which = gui->textures.sporder[i];
		int	drk = cur->alpha;
		if (gui->cam.dark)
			drk = bind(drk - (gui->cam.dark * (cur->dist + 1) / 8.0), 1, 255);
		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * gui->textures.width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transf.y > 0 && stripe > 0 && stripe < SCRWIDTH && transf.y < ZBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y - (gui->cam.pitch * SCRHEIGHT)) * 256 - SCRHEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * gui->textures.height) / spriteHeight) / 256;
				int	color;

				if (gui->textures.width * texY + texX < 0)
					color = 0x00FFFFFF;
				else
					color = pixget(cur->frames[cur->fcur],
				gui->textures.width * texY + texX, 0); //get current color from the texture texture[sprite[spriteOrder[i]].texture][gui->textures.width * texY + texX]
				if ((color & 0x00FFFFFF) != 0) // use alpha
					pixput(gui->buffer, stripe, y, color | (drk << 24)); //buffer[y][stripe] = color paint pixel if it isn't black, black is the invisible color
			}
		}
		cur = cur->next;
	}
}
