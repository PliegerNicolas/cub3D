/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:56:23 by emis              #+#    #+#             */
/*   Updated: 2023/08/17 19:27:10 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "graphics.h"

//#define RATES ((double[]){0.01, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1})

static void	set_rates_array(double *rates)
{
	size_t	i;

	srand(time(NULL));
	i = 0;
	rates[i++] = 0.01;
	while (i < RATE_NB)
		rates[i++] = 0.1;
	rates[RATE_HEAL] = 1;
	rates[RATE_ARMOR_UP] = 2;
	rates[RATE_SHOOT] = 0.5;
	rates[RATE_WEAPON] = 0.05;
}

int	nextframe(enum e_rates frnb)
{
	static clock_t	last[RATE_NB];
	static double	rates[RATE_NB];
	clock_t			cur;

	if (frnb > RATE_NB)
		return (0);
	if (!rates[0])
		set_rates_array(rates);
	cur = clock();
	if ((double)(cur - last[frnb]) / (double)CLOCKS_PER_SEC < rates[frnb])
		return (0);
	last[frnb] = cur;
	return (1);
}
