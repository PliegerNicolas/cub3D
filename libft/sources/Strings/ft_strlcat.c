/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:12:19 by emis              #+#    #+#             */
/*   Updated: 2022/11/11 10:52:55 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	destlen;

	i = 0;
	if (size)
		destlen = ft_strlen(dest);
	if (size == 0 || destlen > size)
		return (size + ft_strlen(src));
	while (i + destlen < size - 1 && src[i])
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + ft_strlen(src));
}
