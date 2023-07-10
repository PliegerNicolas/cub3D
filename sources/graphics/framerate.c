/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:56:23 by emis              #+#    #+#             */
/*   Updated: 2023/07/10 12:01:50 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

# define FRAMES 10

# define RATES ((double[]){0.01, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1})

int	nextframe(size_t frnb)
{
	static clock_t	last[FRAMES];
	clock_t			cur;

	if (frnb > FRAMES)
		return (0);
	cur = clock();
	if ((double)(cur - last[frnb]) / (double)CLOCKS_PER_SEC < RATES[frnb])
		return (0);
	last[frnb] = cur;
	return (1);
}