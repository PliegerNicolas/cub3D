/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_speed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:03:11 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/16 06:05:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

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
