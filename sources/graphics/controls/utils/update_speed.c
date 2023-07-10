/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_speed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:03:11 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/08 08:26:59 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

/*
static bool	double_is_zero(double num)
{
	double	epsilon;

	epsilon = 1e-9;
	return (num > -epsilon && num < epsilon);
}
*/

void	update_speed(double *current_speed, double target_speed,
	double acceleration_rate)
{
	if (*current_speed - acceleration_rate > target_speed)
		*current_speed -= acceleration_rate;
	else if (*current_speed + acceleration_rate < target_speed)
		*current_speed += acceleration_rate;
	else
		*current_speed = target_speed;
}
