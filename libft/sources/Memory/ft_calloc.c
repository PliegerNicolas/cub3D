/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:48:06 by emis              #+#    #+#             */
/*   Updated: 2022/11/10 15:49:06 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
