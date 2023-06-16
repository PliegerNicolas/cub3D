/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbaj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:37:41 by emis              #+#    #+#             */
/*   Updated: 2023/06/13 16:56:15 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAJ_H
# define GARBAJ_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"

# define GARBMAX 2000

void	*trymalloc(size_t size, int scope);
int		mkorbrk(void *obj, int (*destroyer)(), int failval, int scope);
int		in_dump(void *obj, void *dump[GARBMAX]);
int		garbaj(void *obj, int (*destroyer)(), int order);

/* FREE */

int		freewrap(void *obj);
int		free_ch_ar(char **ar);

/* ERROR */

int		eerror(const char *__s);
void	try(int fail, char *name);

/* WRAPPERS */

int		mlxwrap(void *mlx);

#endif