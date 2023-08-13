/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/08/13 12:39:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static void	strputinfo(t_gui *gui, t_vect where, char *desc, int val)
{
	char	buf[30];
	char	*tmp;

	if (!desc || ft_strlen(desc) > 20)
		return ;
	ft_bzero(buf, 30);
	ft_strlcat(buf, desc, ft_strlen(desc) + 1);
	tmp = ft_itoa(val);
	ft_strlcat(buf, tmp, ft_strlen(buf) + ft_strlen(tmp) + 1);
	free(tmp);
	mlx_string_put(gui->mlx, gui->mlx->win_list, where.x, where.y,
		0xFFFFFF, buf);
}

static void	specs(t_gui *gui, t_vect where)
{
	strputinfo(gui, where, "Pos  X ", gui->cam.posi.x);
	where.x += 70;
	strputinfo(gui, where, "Y ", gui->cam.posi.y);
	where.x -= 70;
	where.y += 15;
	strputinfo(gui, where, "Dir  N ", gui->cam.dir.x * -180);
	where.x += 70;
	strputinfo(gui, where, "E ", gui->cam.dir.y * 180);
	where.x -= 70;
	where.y += 15;
	strputinfo(gui, where, "Pitch   ", gui->cam.pitch);
	where.y += 15;
	strputinfo(gui, where, "Render  ", gui->cam.rndr);
	where.y += 15;
	strputinfo(gui, where, "Zoom    ", gui->cam.zoom * 20);
	where.y += 15;
	strputinfo(gui, where, "Dark    ", gui->cam.dark);
	where.y += 15;
	strputinfo(gui, where, "Sprite  ", gui->textures.spnb);
	where.y += 15;
	strputinfo(gui, where, "Health  ", gui->cam.stat.get[HP]);
	where.y += 15;
	strputinfo(gui, where, "Stamina ", gui->cam.stat.get[STA]);
}

int	render(t_gui *gui)
{
	double	z_buffer[SCRWIDTH];

	if (gui->rendered && ((!gui->keys && !gui->cam.speed.x && !gui->cam.speed.y
				&& !gui->cam.rot_speed.x && !gui->cam.rot_speed.y)
			&& !(gui->cam.rndr & (1 << SPRITES))))
		return (0);
	key_render(gui);
	erase(gui->buffer);
	if (gui->cam.rndr & (1 << FLOORCEIL))
		floor_cast(gui);
	wall_cast(gui, z_buffer);
	if (gui->cam.rndr & (1 << SPRITES))
	{
		sprite_cast(gui, z_buffer);
		weapon(gui);
	}
	hud(gui);
	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, gui->buffer, 0, 0);
	specs(gui, (t_vect){SCRWIDTH - 115, 30});
	gui->rendered = 1;
	return (0);
}
