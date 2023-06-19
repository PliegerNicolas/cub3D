/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/06/19 18:10:01 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

int	pixget(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	return (*(unsigned int*)dst);
}

void	pixput(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int	render(t_gui *gui)
{
	if (gui->rendered && !gui->keys)
		return (0);
	if (gui->keys)
	{
		if (gui->keys & (1 << KP_sprint))
			gui->player.speed = 2;
		else
			gui->player.speed = 1;
		if (gui->keys & (1 << KP_rot_left))
			rotate(&gui->player, 1);
		else if (gui->keys & (1 << KP_rot_right))
			rotate(&gui->player, -1);
		if (gui->keys & (1 << KP_zoom_in))
			zoom(&gui->player, 1);
		else if (gui->keys & (1 << KP_zoom_out))
			zoom(&gui->player, -1);
		move(gui);
	}

	//1D Zbuffer
	double ZBuffer[SCRWIDTH];

	wall_cast(gui, ZBuffer);

	sprite_cast(gui, ZBuffer);

	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, gui->buffer, 0, 0);
	gui->rendered = 1;
	printf("x%fy%fdirx%fdiry%f\n", gui->player.posi.x, gui->player.posi.y,
									gui->player.dir.x, gui->player.dir.y);
	return (0);
}