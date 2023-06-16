/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:02:14 by emis              #+#    #+#             */
/*   Updated: 2023/03/12 16:06:29 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

unsigned int	totlen(int size, char **strs)
{
	unsigned int	sum;
	int				i;

	sum = 0;
	i = -1;
	while (++i < size)
		sum += len(strs[i]);
	return (sum + 1);
}

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	destlen;

	i = 0;
	destlen = len(dest);
	while (src[i] != 0)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (dest);
}

char	*ft_strjointab(int size, char **strs, char *sep)
{
	char			*jon;
	int				i;

	if (size <= 0)
	{
		jon = malloc(sizeof(*sep));
		if (!jon)
			return (NULL);
		jon[0] = 0;
		return (jon);
	}
	jon = malloc(sizeof(char) * (totlen(size, strs) + len(sep) * (size - 1)));
	if (!jon)
		return (NULL);
	jon[0] = 0;
	i = -1;
	while (++i < size - 1)
		ft_strcat(ft_strcat(jon, strs[i]), sep);
	ft_strcat(jon, strs[i]);
	return (jon);
}
