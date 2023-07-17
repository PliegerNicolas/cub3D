/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/07/16 06:58:36 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	specs(t_gui *gui, t_vect where)
{
	char	buf[30];
	char	*tmp;

	ft_bzero(buf, 30);
	ft_strlcat(buf, "X", 2);
	tmp = ft_itoa(gui->cam.posi.x);
	ft_strlcat(buf, tmp, ft_strlen(buf) + ft_strlen(tmp) + 1);
	free(tmp);
	ft_strlcat(buf, " Y", ft_strlen(buf) + 3);
	tmp = ft_itoa(gui->cam.posi.y);
	ft_strlcat(buf, tmp, ft_strlen(buf) + ft_strlen(tmp) + 1);
	free(tmp);
	mlx_string_put(gui->mlx, gui->mlx->win_list, where.x, where.y,
		0xFFFFFF, buf);
}

int	render(t_gui *gui)
{
	double	z_buffer[SCRWIDTH];

	if (gui->rendered && ((!gui->keys && !gui->cam.speed.x && !gui->cam.speed.y
				&& !gui->cam.rot_speed.x && !gui->cam.rot_speed.y)
			&& gui->cam.rndr < SPRITES))
		return (0);
	key_render(gui);
	erase(gui->buffer);
	if (gui->cam.rndr == FLOORCEIL)
		floor_cast(gui);
	wall_cast(gui, z_buffer);
	if (gui->cam.rndr >= SPRITES)
	{
		sprite_cast(gui, z_buffer);
		weapon(gui);
	}
	minimap(gui);
	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, gui->buffer, 0, 0);
	specs(gui, (t_vect){SCRWIDTH / 2, 30});
	gui->rendered = 1;
	return (0);
}
