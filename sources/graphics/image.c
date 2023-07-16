/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:10:07 by emis              #+#    #+#             */
/*   Updated: 2023/07/16 11:04:37 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	pixget(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

int	color_mixer(int from, int to, int alpha)
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
	if (alpha)
		*(unsigned int *)dst = color_mixer(*(unsigned int *)dst, color, alpha);
	else
		*(unsigned int *)dst = color;
}

void	erase(t_img *img)
{
	char	*dst;
	int		x;
	int		y;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			dst = img->data + (y * img->size_line + x * (img->bpp / 8));
			*(unsigned int *)dst = 0;
		}
	}
}

void	imgput(t_img *dest, int x, int y, t_img *img)
{
	char	*dst;
	char	*frm;
	int		dx;
	int		dy;

	dy = -1;
	while (++dy < img->height && y + dy < dest->height)
	{
		dx = -1;
		while (++dx < img->width && x + dx < dest->width)
		{
			frm = img->data + (dy * img->size_line + dx * (img->bpp / 8));
			dst = dest->data;
			dst += ((y + dy) * dest->size_line + (x + dx) * (dest->bpp / 8));
			if ((*(unsigned int *)frm & 0x00FFFFFF) != 0)
				*(unsigned int *)dst = *(unsigned int *)frm;
		}
	}
}
