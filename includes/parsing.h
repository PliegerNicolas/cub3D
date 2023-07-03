/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:34:04 by emis              #+#    #+#             */
/*   Updated: 2023/07/03 04:47:58 by nicolas          ###   ########.fr       */
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

enum e_map_tile
{
	floor_tile = 0,
	wall_tile = 1,
	mob_tile = 2,
	spawn_north_tile = 3,
	spawn_south_tile = 4,
	spawn_west_tile = 5,
	spawn_east_tile = 6,
	invalid_tile = -1
};

enum e_type_identifier
{
	north_texture_path = 1,
	south_texture_path = 2,
	east_texture_path = 3,
	west_texture_path = 4,
	floor_texture_path = 5,
	ceiling_texture_path = 6,
	floor_color = 7,
	ceiling_color = 8,
	not_found = 0
};

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

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
