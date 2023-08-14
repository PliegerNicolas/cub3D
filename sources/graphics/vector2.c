/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:08:42 by emis              #+#    #+#             */
/*   Updated: 2023/08/14 15:43:26 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_vect	v_add(t_vect v, t_vect w)
{
	t_vect	add;

	add.x = v.x + w.x;
	add.y = v.y + w.y;
	return (add);
}

t_vect	v_sub(t_vect v, t_vect w)
{
	t_vect	sub;

	sub.x = v.x - w.x;
	sub.y = v.y - w.y;
	return (sub);
}

t_vect	v_mul(t_vect v, t_vect w)
{
	t_vect	mul;

	mul.x = v.x * w.x;
	mul.y = v.y * w.y;
	return (mul);
}

t_vect	v_div(t_vect v, t_vect w)
{
	t_vect	div;

	div.x = v.x / (w.x + (w.x == 0));
	div.y = v.y / (w.y + (w.y == 0));
	return (div);
}

t_vect	v_rot(t_vect v, t_vect w)
{
	t_vect	rot;

	rot.x = -(v.x * w.x + v.y * -w.y);
	rot.y = (v.x * -w.y - v.y * w.x);
	return (rot);
}
