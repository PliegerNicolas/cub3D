/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:59:39 by emis              #+#    #+#             */
/*   Updated: 2023/07/26 15:00:55 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	dot(t_img *img, int px, int py, int color)
{
	int	x;
	int	y;

	y = py - 3;
	while (++y < py + 3)
	{
		x = px - 3;
		while (++x < px + 3)
			pixput(img, x, y, color);
	}
}

static float	sign(t_vect p1, t_vect p2, t_vect p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y)
		- (p2.x - p3.x) * (p1.y - p3.y);
}

static bool	bsp(t_vect a, t_vect b, t_vect c, t_vect point)
{
	float	d1, d2, d3;
	bool	has_neg, has_pos;

	d1 = sign(point, a, b);
	d2 = sign(point, b, c);
	d3 = sign(point, c, a);
	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
	return !(has_neg && has_pos);
}

void	tri(t_img *img, t_vect at, t_vect dir, int color)
{
	t_vect	p;
	t_vect	a;
	t_vect	b;
	t_vect	c;

	a = v_add(at, scale(dir, 0.8));
	b = v_add(at, v_add(scale(dir, -0.8), scale(perp(dir), 0.5)));
	c = v_add(at, v_add(scale(dir, -0.8), scale(perp(scale(dir, -1)), 0.5)));
	p.y = at.y - 20;
	while (p.y += 1, p.y < at.y + 20)
	{
		p.x = at.x - 20;
		while (p.x += 1, p.x < at.x + 20)
			if (bsp(a, b, c, p))
				pixput(img, p.y, p.x, color);
	}
}