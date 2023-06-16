/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbaj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 11:56:44 by emis              #+#    #+#             */
/*   Updated: 2023/06/13 15:40:12 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/garbaj.h"

void	*trymalloc(size_t size, int scope)
{
	void	*obj;

	obj = malloc(size);
	if (!obj)
	{
		eerror("Malloc");
		garbaj(NULL, NULL, 0);
		exit(1);
	}
	ft_bzero(obj, size);
	garbaj(obj, &freewrap, scope);
	return (obj);
}

int	mkorbrk(void *obj, int (*destroyer)(), int failval, int scope)
{
	if (!destroyer)
		return (-1);
	if (failval || !obj)
	{
		if (errno)
			eerror(__func__);
		garbaj(NULL, NULL, 0);
		exit(1);
	}
	garbaj(obj, destroyer, scope);
	return (0);
}

int	in_dump(void *obj, void *dump[GARBMAX])
{
	static void	**dpcp;
	int			i;

	i = -1;
	if (!dpcp)
		dpcp = dump;
	while (++i < GARBMAX)
		if (obj == dpcp[i])
			return (i);
	return (-1);
}

int	garbaj(void *obj, int (*destroyer)(), int order)
{
	static void	*dump[GARBMAX];
	static int	(*dstr[GARBMAX])();
	static int	scope[GARBMAX];
	static int	idx;
	int			p;

	if (obj && destroyer && in_dump(obj, dump) == -1)
	{
		if (idx == GARBMAX)
			return (eerror("Error\nGarbaj full.\n"),
				garbaj(NULL, NULL, 0), exit(1), 1);
		dump[idx] = obj;
		dstr[idx] = destroyer;
		scope[idx] = order;
		return (idx++, 0);
	}
	else if (obj && in_dump(obj, dump) != -1)
		return (p = dstr[in_dump(obj, dump)](obj),
			dump[in_dump(obj, dump)] = NULL, p);
	p = idx;
	while (!obj && !destroyer && p && p--)
		if (dump[p] && (!order || scope[p] == order) && !dstr[p](dump[p]))
			dump[p] = NULL;
	return (0);
}

// printf("Destroy %d\n", idx);
/*
int (*get_destroyer(void *obj, void *dump[GARBMAX], int (*dstr[GARBMAX])()))()
{
	int	i;

	i = -1;
	while (++i < GARBMAX)
		if (obj == dump[i])
			return (dstr[i]);
	return (NULL);
}
*/