/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:08:42 by emis              #+#    #+#             */
/*   Updated: 2023/07/26 13:39:56 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_vect	v_add(t_vect v, t_vect w)
{
	return ((t_vect){v.x + w.x, v.y + w.y});
}

t_vect	v_sub(t_vect v, t_vect w)
{
	return ((t_vect){v.x - w.x, v.y - w.y});
}

t_vect	v_mul(t_vect v, t_vect w)
{
	return ((t_vect){v.x * w.x, v.y * w.y});
}

t_vect	v_div(t_vect v, t_vect w)
{
	return ((t_vect){v.x / (w.x + (w.x == 0)), v.y / (w.y + (w.y == 0))});
}
