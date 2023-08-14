/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_keys_and_btns_arr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 07:02:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/08/14 15:33:34 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	initialize_keys_arr(t_kbind *keys)
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
	keys[13] = space;
}

static void	initialize_btns_arr(t_bprs *mouse_btns)
{
	mouse_btns[0] = 0;
	mouse_btns[1] = left_click;
	mouse_btns[2] = mid_click;
	mouse_btns[3] = right_click;
	mouse_btns[4] = scroll_up;
	mouse_btns[5] = scroll_down;
}

int	get_keypress_index(int keycode)
{
	static t_kbind	keys[14];
	size_t			i;

	if (!keys[1])
		initialize_keys_arr(keys);
	i = 0;
	while (i < sizeof(keys) / sizeof(*keys))
	{
		if (keycode == (int)keys[i])
			return (i);
		i++;
	}
	return (-1);
}

int	get_mousepress_index(int keycode)
{
	static t_bprs	btns[6];
	size_t			i;

	if (!btns[1])
		initialize_btns_arr(btns);
	i = 0;
	while (i < sizeof(btns) / sizeof(*btns))
	{
		if (keycode == (int)btns[i])
			return (i);
		i++;
	}
	return (-1);
}
