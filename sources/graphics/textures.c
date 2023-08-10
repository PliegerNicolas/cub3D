/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:23:46 by emis              #+#    #+#             */
/*   Updated: 2023/08/10 18:50:44 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_img	*load_texture(t_gui *gui, char *path)
{
	t_img	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(gui->mlx, path, &w, &h);
	if (!img)
		return (errno = 1, eerror("Failure to load texture."), NULL);
	mlximgwrap(gui->mlx);
	garbaj(img, mlximgwrap, 1);
	return (img);
}

bool	load_texture_arr(t_gui *gui, t_img ***where, char *path, int size)
{
	static int	which;

	if (!*where)
	{
		*where = trymalloc(sizeof(t_img *) * size, 1);
		which = 0;
	}
	(*where)[which++] = load_texture(gui, path);
	return (!(*where)[which - 1]);
}
