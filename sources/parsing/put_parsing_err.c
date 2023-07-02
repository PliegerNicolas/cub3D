/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_parsing_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:57:35 by nplieger          #+#    #+#             */
/*   Updated: 2023/06/23 16:44:56 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

#define B_RED "\001\033[1;31m\002"
#define RED "\001\033[31m\002"
#define CYAN "\001\033[36m\002"
#define WHITE "\001\033[0m\002"

void	put_parsing_err(char *err_msg)
{
	ft_putstr_fd(B_RED, STDERR_FILENO);
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(WHITE, STDERR_FILENO);
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd(CYAN, STDERR_FILENO);
	ft_putendl_fd("Expected usage : ./cub3D [*.cub]", STDERR_FILENO);
	ft_putstr_fd(WHITE, STDERR_FILENO);
}
