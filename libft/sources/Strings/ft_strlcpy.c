/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:48:14 by emis              #+#    #+#             */
/*   Updated: 2022/11/08 13:16:39 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = 0;
	while (src[srclen])
		srclen++;
	if (size < 1)
		return (srclen);
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (dest[i] != '\0')
		dest[i] = '\0';
	return (srclen);
}
