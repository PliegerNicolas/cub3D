/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:34:04 by emis              #+#    #+#             */
/*   Updated: 2023/06/27 02:43:31 by nicolas          ###   ########.fr       */
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
# include <stdlib.h>

/* ************************************** */
/* * ENUMERATORS						* */
/* ************************************** */

enum type_identifier
{
	north_texture_path = 1,
	south_texture_path = 2,
	east_texture_path = 3,
	west_texture_path = 4,
	floor_color = 5,
	ceiling_color = 6,
	not_found = 0
};

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

bool					verify_arguments(int argc, char **argv);
void					put_parsing_err(char *err_msg);
int						ft_isspace(int c);

char					*get_type_identifier_data(char *line);

/* text_filter.c */

void					skip_whitespaces(char *line, size_t *index);
int						skip_comments(char *line, size_t *index);

/* type_identifiers.c */

enum type_identifier	set_type_identifier(char *line, size_t *index);

#endif
