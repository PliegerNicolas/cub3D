/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:50:30 by emis              #+#    #+#             */
/*   Updated: 2022/11/27 12:52:58 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <unistd.h>
# include <stdlib.h>

//UTILS
int		append(char **str, char *toappend, int lenstr, int lenapn);
int		nxtbsn(char *buf, int bsize);
int		start_line(char **ln, char **buf);
char	*end_line(char **line);
//GNL
char	*get_next_line(int fd);

#endif