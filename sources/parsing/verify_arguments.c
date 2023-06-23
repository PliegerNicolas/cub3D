/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:59:43 by nplieger          #+#    #+#             */
/*   Updated: 2023/06/23 15:09:38 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "graphics.h"

static bool	verify_map_path(char *file_name)
{
	int	len;

	len = ft_strlen(file_name);
	if (len < 4 || ft_strncmp(file_name + len - 4, ".cub", 5) != 0)
		return (put_parsing_err("Invalid file_name."), true);
	if (access(file_name, F_OK | R_OK) < 0)
		return (put_parsing_err("File doesn't exist or permission denied."),
			true);
	return (false);
}

bool	verify_arguments(int argc, char **argv)
{
	if (argc != 2)
		return (put_parsing_err("Wrong number of arguments given."), true);
	if (verify_map_path(argv[1]))
		return (true);
	return (false);
}
