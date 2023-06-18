/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:44:19 by emis              #+#    #+#             */
/*   Updated: 2023/06/18 16:38:09 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/garbaj.h"

int	mlxwrap(void *mlx)
{
	if (mlx_destroy_display(mlx))
		return (1);
	free(mlx);
	return (0);
}

int	mlximgwrap(void *mlximg)
{
	static void	*mlx;

	if (!mlx)
		return (mlx = mlximg, 0);
	if (mlximg && mlximg != mlx && mlx_destroy_image(mlx, mlximg))
		return (1);
	return (0);
}
