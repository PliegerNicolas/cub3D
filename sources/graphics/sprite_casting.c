/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:26:04 by emis              #+#    #+#             */
/*   Updated: 2023/06/20 15:18:21 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/graphics.h"

static void	sort_sprites(t_tex *tex, t_vect *from)
{
	int	i;
	int	tmp;

	i = -1;
	while (++i < tex->spnb)
	{
		tex->sporder[i] = i;
		tex->spdist[i] = ((from->x - tex->sprites[i].posi.x)
			* (from->x - tex->sprites[i].posi.x)
			+ (from->y - tex->sprites[i].posi.y)
			* (from->y - tex->sprites[i].posi.y)); //sqrt not taken, unneeded
	}
	i = -1;
	while (++i < tex->spnb - 1)
	{
		if (tex->spdist[tex->sporder[i]] < tex->spdist[tex->sporder[i + 1]])
		{
			tmp = tex->sporder[i];
			tex->sporder[i] = tex->sporder[i + 1];
			tex->sporder[i + 1] = tmp;
			i = -1;
		}
	}
}

// translate sprite position to relative to camera
// transform sprite with the inverse camera matrix
// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
// [ planeY   dirY ]                                          [ -planeY  planeX ]
t_vect	transform(t_tex *tex, t_play *play, int i)
{
	t_vect	sprite;
	double	invDet;

	sprite = (t_vect){tex->sprites[tex->sporder[i]].posi.x - play->posi.x,
		tex->sprites[tex->sporder[i]].posi.y - play->posi.y};
	invDet = 1.0 / (play->plane.x * (play->dir.y * play->zoom)
		- (play->dir.x * play->zoom) * play->plane.y);
	return ((t_vect){
		invDet * ((play->dir.y * play->zoom) * sprite.x
		- (play->dir.x * play->zoom) * sprite.y),
		invDet * (-play->plane.y * sprite.x
		+ play->plane.x * sprite.y)
		});
}

int	bind(int val, int min, int max)
{
	if (val < min)
		return (min);
	if (val >= max)
		return (max - 1);
	return (val);
}

void	sprite_cast(t_gui *gui, double ZBuffer[SCRWIDTH])
{
	t_vect	transf;

	sort_sprites(&gui->textures, &gui->cam.posi);

	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < gui->textures.spnb; i++)
	{
		transf = transform(&gui->textures, &gui->cam, i);

		int spriteScreenX = (int)((SCRWIDTH / 2) * (1 + transf.x / transf.y));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(SCRHEIGHT / (transf.y))); //using 'transformY' instead of the real distance prevents fisheye
		
		// int pitch = 100;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = bind(-spriteHeight / 2 + SCRHEIGHT / 2 + gui->cam.pitch, 0, SCRHEIGHT);
		// if (drawStartY < 0)
		// 	drawStartY = 0;
		int drawEndY = bind(spriteHeight / 2 + SCRHEIGHT / 2 + gui->cam.pitch, 0, SCRHEIGHT);
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
				int d = (y - gui->cam.pitch) * 256 - SCRHEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * gui->textures.height) / spriteHeight) / 256;
				int color = pixget(gui->textures.sprites[gui->textures.sporder[i]].frames[0], gui->textures.width * texY + texX, 0); //get current color from the texture texture[sprite[spriteOrder[i]].texture][gui->textures.width * texY + texX]
				if ((color & 0x00FFFFFF) != 0) // use alpha
					pixput(gui->buffer, stripe, y, color | (200 << 24)); //buffer[y][stripe] = color paint pixel if it isn't black, black is the invisible color
			}
		}
	}
}