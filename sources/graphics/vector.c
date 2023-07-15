/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:22:49 by emis              #+#    #+#             */
/*   Updated: 2023/07/10 13:48:53 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double	magnitude(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	angle(t_vect v1, t_vect v2)
{
	return (acos((v1.x * v2.x + v1.y * v2.y)
			/ (magnitude(v1) * magnitude(v2))));
}

t_vect	delta(t_vect from, t_vect to)
{
	t_vect	d;
	double	mag;

	d.x = to.x - from.x;
	d.y = to.y - from.y;
	mag = magnitude(d);
	if (!mag)
		return (d);
	d.x /= mag;
	d.y /= mag;
	return (d);
}
