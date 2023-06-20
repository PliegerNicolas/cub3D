/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:03:16 by emis              #+#    #+#             */
/*   Updated: 2023/06/20 15:08:15 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

int	pixget(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	return (*(unsigned int*)dst);
}

static int	color_shifter(int from, int to, int alpha)
{
	int	color;

	color = 0;
	color |= ((from >> 16) & 255) * (255 - alpha) / 255
		+ ((to >> 16) & 255) * (alpha) / 255;
	color = color << 8;
	color |= ((from >> 8) & 255) * (255 - alpha) / 255
		+ ((to >> 8) & 255) * (alpha) / 255;
	color = color << 8;
	color |= ((from >> 0) & 255) * (255 - alpha) / 255
		+ ((to >> 0) & 255) * (alpha) / 255;
	return (color);
}

void	pixput(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		alpha;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	alpha = (color >> 24) & 255;
	if (alpha) //printf("%x, %x\n", (((*(unsigned int*)dst) * (256 - alpha)) / 256), (color * alpha) / 256), 
		*(unsigned int*)dst = color_shifter(*(unsigned int*)dst, color, alpha);
	else
		*(unsigned int*)dst = color;
}

int	render(t_gui *gui)
{
	if (gui->rendered && !gui->keys)
		return (0);
	if (gui->keys)
	{
		if (gui->keys & (1 << KP_sprint))
			gui->cam.speed = 2;
		else
			gui->cam.speed = 1;
		if (gui->keys & (1 << KP_rot_left))
			rotate(&gui->cam, 1);
		else if (gui->keys & (1 << KP_rot_right))
			rotate(&gui->cam, -1);
		if (gui->keys & (1 << KP_zoom_in))
			zoom(&gui->cam, 1);
		else if (gui->keys & (1 << KP_zoom_out))
			zoom(&gui->cam, -1);
		move(gui);
	}

	//1D Zbuffer
	double ZBuffer[SCRWIDTH];

	wall_cast(gui, ZBuffer);

	sprite_cast(gui, ZBuffer);

	mlx_put_image_to_window(gui->mlx, gui->mlx->win_list, gui->buffer, 0, 0);
	gui->rendered = 1;
	printf("x%fy%fdirx%fdiry%f\n", gui->cam.posi.x, gui->cam.posi.y,
									gui->cam.dir.x, gui->cam.dir.y);
	return (0);
}