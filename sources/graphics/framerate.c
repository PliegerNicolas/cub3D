/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:56:23 by emis              #+#    #+#             */
/*   Updated: 2023/08/14 11:29:16 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <time.h>

#define FRAMES 10

//#define RATES ((double[]){0.01, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1})

static void	set_rates_array(double *rates)
{
	size_t	i;

	i = 0;
	rates[i++] = 0.01;
	while (i < FRAMES)
		rates[i++] = 0.1;
	rates[RATE_SHOOT] = 0.5;
}

int	nextframe(size_t frnb)
{
	static clock_t	last[FRAMES];
	double			rates[FRAMES];
	clock_t			cur;

	if (frnb > FRAMES)
		return (0);
	set_rates_array(rates);
	cur = clock();
	if ((double)(cur - last[frnb]) / (double)CLOCKS_PER_SEC < rates[frnb])
		return (0);
	last[frnb] = cur;
	return (1);
}
