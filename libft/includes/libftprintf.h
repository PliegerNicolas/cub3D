/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:52:26 by emis              #+#    #+#             */
/*   Updated: 2022/12/06 16:10:05 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include "libft.h"

//ARGS
char	*strfrmchr(char c);

char	*strfrmstr(char *str, int fr);

char	*strfrmptr(void *ptr);

char	*strfrmhex(unsigned int hex, int big);

//IN LIBFT

char	*mknbr(unsigned int n);

//UTIL
int		insetend(char const *set, char c, char end);

char	*tnx(char *fmt, char c);

char	*tnxnb(char *fmt);

char	*tnxhx(char *fmt);

char	*ft_strncpyfree(char *dest, char *src, unsigned int n);

//FLUT
void	addprefix(char **res, char prefix);

char	*mkfield(int size, int zeropad);

//FLAG
char	*flagchan(int arg, char *fmt, char *res);

//FT_PRINTF
int		ft_printf(const char *s, ...);

#endif
