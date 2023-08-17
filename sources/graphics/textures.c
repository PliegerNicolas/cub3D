/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:23:46 by emis              #+#    #+#             */
/*   Updated: 2023/08/17 17:31:50 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_img	*load_texture(t_gui *gui, char *path, int checkdim)
{
	static int	sw;
	static int	sh;
	t_img		*img;
	int			w;
	int			h;

	img = mlx_xpm_file_to_image(gui->mlx, path, &w, &h);
	if (!img)
		return (errno = 1, eerror("Failure to load texture.\n"), NULL);
	mlximgwrap(gui->mlx);
	garbaj(img, mlximgwrap, 1);
	if (!checkdim)
	{
		sw = w;
		sh = h;
	}
	else if (w != sw || h != sh)
		return (errno = 1, eerror("Texture size mismatch.\n"), NULL);
	return (img);
}

bool	load_texture_arr(t_gui *gui, t_img ***where, char *path, int size)
{
	static int	which;
	static int	sizecheck;

	if (!*where)
	{
		*where = trymalloc(sizeof(t_img *) * size, 1);
		which = 0;
		sizecheck = size;
	}
	if (size != sizecheck)
		return (errno = 1, eerror("Texture array size mismatch.\n"), 1);
	if (which == size)
		return (errno = 1, eerror("Texture array full.\n"), 1);
	(*where)[which] = load_texture(gui, path, which);
	return (!(*where)[which++]);
}
