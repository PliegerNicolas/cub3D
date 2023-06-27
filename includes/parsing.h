/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:34:04 by emis              #+#    #+#             */
/*   Updated: 2023/06/27 18:07:19 by nicolas          ###   ########.fr       */
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

enum e_type_identifier
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

typedef struct s_map_ctrl
{
	char				*line;
	size_t				len;
	struct s_map_ctrl	*next;
}	t_map_ctrl;

/* ************************************** */
/* * GLOBAL VAR							* */
/* ************************************** */

/* ************************************** */
/* * MACRO								* */
/* ************************************** */

//# define SYMBOLS ((t_sym[]){NORTH, SOUTH, EAST, WEST, FLOOR, WALL})
//# define SYMSTR ("NSEW01") // to check map use strchr on this string ?

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

enum e_type_identifier	set_type_identifier(char *line, size_t *index);

/* free.c */

void					free_map_ctrl(t_map_ctrl **map_ctrl);

/* is_incharset.c */

int						is_incharset(unsigned char c, char *charset);

/* parse_map.c */

bool					parse_map(char *line, t_map_ctrl **map_ctrl);

/* goto_eof.c */

void					goto_eof(int fd);

#endif
