/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:34:04 by emis              #+#    #+#             */
/*   Updated: 2023/06/26 07:08:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSING_H
# define PARSING_H

/* ************************************** */
/* * INCLUDES							* */
/* ************************************** */

# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

/* ************************************** */
/* * ENUMERATORS						* */
/* ************************************** */

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

typedef enum e_map_symbols
{
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	FLOOR = '0',
	WALL = '1'
}	t_sym;

/* ************************************** */
/* * GLOBAL VAR							* */
/* ************************************** */

/* ************************************** */
/* * MACRO								* */
/* ************************************** */

# define SYMBOLS ((t_sym[]){NORTH, SOUTH, EAST, WEST, FLOOR, WALL})
# define SYMSTR ("NSEW01") // to check map use strchr on this string ?

/* ************************************** */
/* * FUNCTIONS							* */
/* ************************************** */

bool	verify_arguments(int argc, char **argv);
void	put_parsing_err(char *err_msg);
int		ft_isspace(int c);

/* text_filter.c */

void	skip_whitespaces(char *line, size_t *index);
int		skip_comments(char *line, size_t *index);

#endif
