/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:39:56 by emis              #+#    #+#             */
/*   Updated: 2023/06/23 16:23:28 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

int	bind(int val, int min, int max)
{
	if (val < min)
		return (min);
	if (val >= max)
		return (max - 1);
	return (val);
}

int	loopbind(int val, int min, int max)
{
	if (val < min)
		return (max - 1);
	if (val >= max)
		return (min);
	return (val);
}

double	invSafe(double x)
{
	if (x == 0)
		return (1e30);
	return (fabs(1 / x));
}

t_vect	delta(t_vect from, t_vect to)
{
	t_vect	d;
	double	mag;

	d.x = to.x - from.x;
	d.y = to.y - from.y;
	mag = sqrt(d.x * d.x + d.y * d.y);
	d.x /= mag;
	d.y /= mag;
	return (d);
}
