/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:18:56 by emis              #+#    #+#             */
/*   Updated: 2023/08/13 12:03:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static int color_angle(t_gui *gui, t_vect ori, t_vect pt)
{
    double alpha;
    int color;

    alpha = angle((t_vect){ori.x, -ori.y}, v_sub(pt, ori))
            * (1 - 2 * (pt.x + pt.y < ori.x + ori.y));
    color = (int)((255.0 * alpha) / M_PI);
    if (color < 0 && (-color) < (255 - 255 * (gui->cam.stat.max[XP]
			- gui->cam.stat.get[XP]) / gui->cam.stat.max[XP]))
        color = MAPBLUE;
    else if (color >= 0 && color < (85 - 85 * (gui->cam.stat.max[HP]
			- gui->cam.stat.get[HP]) / gui->cam.stat.max[HP]))
        color = MAPRED;
    else if (color > 85 && color < (170 - 85 * (gui->cam.stat.max[ARM]
			- gui->cam.stat.get[ARM]) / gui->cam.stat.max[ARM]))
        color = MAPYEL;
    else if (color > 170 && color > (170 + 85 * (gui->cam.stat.max[STA]
			- gui->cam.stat.get[STA]) / gui->cam.stat.max[STA]))
        color = MAPGREEN;
    else
        color = MAPBLACK;
    return color;
}


static void	curvybars(t_gui *gui, t_vect where, int s)
{
	int		x;
	int		y;
	double	m;

	x = 0;
	while (++x < s * s + 2 * s)
	{
		y = 0;
		while (++y < s * s + 2 * s)
		{
			m = magnitude((t_vect){x - s - s * s / 2.0, y - s - s * s / 2.0});
			if (m < (s * s / 2) || m > (s * s / 2) + s)
				continue ;
			pixput(gui->buffer, y + where.y, x + where.x,
				color_angle(gui, (t_vect){s * s / 2 + s, s * s / 2 + s},
					(t_vect){x, y}) | 0xCC << 24);
		}
	}
}

void	hud(t_gui *gui)
{
	int	s;

	if (gui->cam.rndr & (1 << MINIMAP))
	{
		s = 14;
		minimap(gui, (t_vect){s, s}, s, !(gui->keys & (1 << KP_map)));
		curvybars(gui, (t_vect){0, 0}, s);
	}
	else
		s = fullmap(gui, (t_vect){0, 0});
}
