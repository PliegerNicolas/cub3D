/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:39:56 by emis              #+#    #+#             */
/*   Updated: 2023/07/01 15:23:07 by emis             ###   ########.fr       */
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
