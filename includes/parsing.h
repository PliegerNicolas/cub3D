/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:34:04 by emis              #+#    #+#             */
/*   Updated: 2023/08/19 12:48:08 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# ifndef BONUS
#  define BONUS 1
# endif

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

typedef enum e_map_tile
{
	invalid_tile = -1,
	floor_tile,
	wall_tile,
	mob_tile,
	pack_tile,
	obj_tile,
	spawn_north_tile,
	spawn_south_tile,
	spawn_west_tile,
	spawn_east_tile,
	door_tile = 43
}	t_maptile;

typedef enum e_type_identifier
{
	north_texture = 1,
	south_texture = 2,
	west_texture = 3,
	east_texture = 4,
	floor_texture = 5,
	ceiling_texture = 6,
	floor_color = 7,
	ceiling_color = 8,
	door_texture = 9,
	weapon_texture = 10,
	sprite_texture = 11,
	not_found = 0
}	t_type_id;

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

typedef struct s_map_ctrl
{
	char				*line;
	size_t				len;
	struct s_map_ctrl	*next;
}	t_map_ctrl;

typedef struct str_to_type_identifier
{
	char		*str;
	t_type_id	ti;
}	t_str_to_ti;

/* ************************************** */
/* * GLOBAL VAR							* */
/* ************************************** */

/* ************************************** */
/* * MACRO								* */
/* ************************************** */

# if BONUS == 1
#  define MAPTOKENS "01NSWEMPOD"
# else
#  define MAPTOKENS "01NSWE"
# endif

/* ************************************** */
/* * FUNCTIONS							* */
/* ************************************** */

bool					verify_arguments(int argc, char **argv);
void					put_parsing_err(char *err_msg);
int						ft_isspace(int c);

char					*get_type_identifier_data(char *line);

/* text_filter.c */

void					rm_eol(char *line);
void					skip_whitespaces(char *line, size_t *i);
void					skip_comments(char *line, size_t *i,
							bool *is_commented);

/* type_identifiers.c */

enum e_type_identifier	set_type_identifier(char *line, size_t *index);

/* free_2.c */

void					free_str_arr(char **arr);
void					free_map_ctrl(t_map_ctrl **map_ctrl);

/* is_incharset.c */

int						is_incharset(unsigned char c, char *charset);

/* parse_map.c */

bool					parse_map(char *line, t_map_ctrl **map_ctrl);

/* goto_eof.c */

void					goto_eof(int fd);

/* cpy_int_arr.c */

int						**copy_int_arr(int **arr, size_t rowsize,
							size_t colsize);
void					free_int_arr(int **int_arr, size_t rowsize);

#endif
