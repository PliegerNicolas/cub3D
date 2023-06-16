/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:35:38 by emis              #+#    #+#             */
/*   Updated: 2023/02/28 13:57:00 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(char *str, char c)
{
	int	i;
	int	w;

	i = -1;
	w = 0;
	while (str[++i])
	{
		while (str[i] == c && str[i + 1])
			i++;
		if (!(str[i] == c))
			w++;
		while (!(str[i] == c) && str[i + 1])
			i++;
	}
	return (w);
}

static char	*getword(char *str, char c)
{
	char	*wrd;
	int		j;
	int		k;

	k = -1;
	j = -1;
	while (str[++k])
		if (str[k] == c)
			break ;
	wrd = malloc(sizeof(char) * (k + 1));
	wrd[k] = 0;
	while (++j < k)
		wrd[j] = str[j];
	return (wrd);
}

char	**ft_split(char *str, char c)
{
	char	**tab;
	int		i;
	int		w;

	i = -1;
	w = -1;
	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (countwords(str, c) + 1));
	if (!tab)
		return (NULL);
	tab[countwords(str, c)] = 0;
	while (str[++i] && countwords(str, c) != 0)
	{
		while (str[i] == c && str[i + 1])
			i++;
		if (!(str[i] == c))
			tab[++w] = getword(&str[i], c);
		while (!(str[i] == c) && str[i + 1])
			i++;
	}
	return (tab);
}

/*
#include <stdio.h>

int		main(void)
{
	char **tab;
	int i = 0;

	tab = ft_split("Bonsoir je m'appelle bob yo", ' ');
	while(i < 5)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
*/