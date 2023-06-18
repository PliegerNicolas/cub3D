/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:34:04 by emis              #+#    #+#             */
/*   Updated: 2023/06/18 19:52:42 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum e_map_symbols
{
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	FLOOR = '0',
	WALL = '1'
}	t_sym;

# define SYMBOLS ((t_sym[]){NORTH, SOUTH, EAST, WEST, FLOOR, WALL})
# define SYMSTR ("NSEW01") // to check map use strchr on this string ?

#endif