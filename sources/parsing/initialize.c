/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:17:24 by nplieger          #+#    #+#             */
/*   Updated: 2023/06/23 17:17:27 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

bool	initialize(int argc, char **argv, t_gui *gui)
{
	int	fd;

	if (verify_arguments(argc, argv))
		return (true);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (put_parsing_err("Unable to open file."), true);
	if (initialize_gui(gui))
		return (close(fd), true);
	return (close(fd), false);
}
