/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:16:31 by emis              #+#    #+#             */
/*   Updated: 2023/06/23 19:27:35 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/graphics.h"

void	weapon(t_gui *gui)
{
	static t_img	**wpn;

	if (!wpn)
		load_texture_arr(gui, &wpn, "textures/wand.xpm", 1);
	imgput(gui->buffer, SCRWIDTH - wpn[0]->width - 1,
		SCRHEIGHT - wpn[0]->height - 1, wpn[0]);
}