/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:10:07 by emis              #+#    #+#             */
/*   Updated: 2023/06/20 16:14:44 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

int	pixget(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	return (*(unsigned int*)dst);
}

static int	color_mixer(int from, int to, int alpha)
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
		*(unsigned int*)dst = color_mixer(*(unsigned int*)dst, color, alpha);
	else
		*(unsigned int*)dst = color;
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
			*(unsigned int*)dst = 0;
		}
	}
}
