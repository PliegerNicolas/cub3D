/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_keys_and_btns_arr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 07:02:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/07/25 14:16:50 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	set_keys_arr(t_kbind *keys)
{
	keys[0] = forth;
	keys[1] = back;
	keys[2] = left;
	keys[3] = right;
	keys[4] = sprint;
	keys[5] = rot_left;
	keys[6] = rot_right;
	keys[7] = rot_up;
	keys[8] = rot_down;
	keys[9] = zoom_in;
	keys[10] = zoom_out;
	keys[11] = interactkey;
	keys[12] = mapkey;
}

void	set_btns_arr(t_bprs *mouse_btns)
{
	mouse_btns[0] = 0;
	mouse_btns[1] = left_click;
	mouse_btns[2] = mid_click;
	mouse_btns[3] = right_click;
	mouse_btns[4] = scroll_up;
	mouse_btns[5] = scroll_down;
}
