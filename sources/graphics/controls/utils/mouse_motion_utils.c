/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 04:13:44 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/18 04:14:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

void	initialize_mouse_motion(t_gui *gui, int last[2])
{
	if (!last[0] && !last[1])
	{
		last[0] = SCRWIDTH / 2;
		last[1] = SCRHEIGHT / 2;
	}
	gui->cam.rot_speed.x = gui->cam.rot_speed_target.x;
	gui->cam.rot_speed.y = gui->cam.rot_speed_target.y;
}
