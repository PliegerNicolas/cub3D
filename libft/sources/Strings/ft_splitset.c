/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:13:15 by emis              #+#    #+#             */
/*   Updated: 2023/02/28 15:11:54 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	issep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	countwords(char *str, char *charset)
{
	int	i;
	int	w;

	i = -1;
	w = 0;
	while (str[++i])
	{
		while (issep(str[i], charset) && str[i + 1])
			i++;
		if (!issep(str[i], charset))
			w++;
		while (!issep(str[i], charset) && str[i + 1])
			i++;
	}
	return (w);
}

static char	*getword(char *str, char *charset)
{
	char	*wrd;
	int		j;
	int		k;

	k = -1;
	j = -1;
	while (str[++k])
		if (issep(str[k], charset))
			break ;
	wrd = malloc(sizeof(char) * (k + 1));
	if (!wrd)
		return (NULL);
	wrd[k] = 0;
	while (++j < k)
		wrd[j] = str[j];
	return (wrd);
}

char	**ft_splitset(char *str, char *charset)
{
	char	**tab;
	int		i;
	int		w;

	i = -1;
	w = -1;
	if (!str || !charset)
		return (NULL);
	tab = malloc(sizeof(char *) * (countwords(str, charset) + 1));
	if (!tab)
		return (NULL);
	tab[countwords(str, charset)] = 0;
	while (str[++i] && countwords(str, charset) != 0)
	{
		while (issep(str[i], charset) && str[i + 1])
			i++;
		if (!issep(str[i], charset))
			tab[++w] = getword(&str[i], charset);
		while (!issep(str[i], charset) && str[i + 1])
			i++;
	}
	return (tab);
}
