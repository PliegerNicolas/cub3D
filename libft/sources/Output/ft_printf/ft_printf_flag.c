/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:48:17 by emis              #+#    #+#             */
/*   Updated: 2022/11/19 14:29:58 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*field(char *res, int rjustify, int zeropad, int minf)
{
	char	*field;
	int		i;

	if (minf <= (int)ft_strlen(res) && !(zeropad < 0
			&& -(zeropad + 1) < (int)ft_strlen(res)))
		return (res);
	if (zeropad < 0 && -(zeropad + 1) < (int)ft_strlen(res))
		field = mkfield(-(zeropad + 1), 0);
	else
		field = mkfield(minf, zeropad == 1);
	if (!field)
		return (NULL);
	i = -1;
	while (zeropad > -1 && res[++i])
		field[(rjustify * (minf - (int)ft_strlen(res))) + i] = res[i];
	while (zeropad < 0 && field[++i] && i < -(zeropad + 1) && res[i - (i > 0)])
		field[i] = res[i];
	if (ft_atoi(res) < 0 && *tnx(res, '-') && zeropad == 1 && field[0] == '0')
	{
		field[0] = '-';
		*(tnxnb(field) - 1) = '0';
	}
	free(res);
	return (field);
}

static char	*zeroflag(char *fmt)
{
	int	i;

	i = -1;
	while (fmt[++i] && fmt[i] != '0')
		;
	if (fmt[i] == '0' && tnxnb(fmt) > &fmt[i])
		return (&fmt[i]);
	return (NULL);
}

static char	*prefix(int arg, char *fmt, char *res)
{
	char	*fixed;
	int		sind;
	char	pfx;

	if (!insetend("dixX", fmt[arg], 0))
		return (res);
	sind = insetend("xX", fmt[arg], 0);
	fixed = res;
	if (!fixed || (sind && !insetend(fmt, '#', 0)))
		return (NULL);
	if (sind)
		pfx = fmt[arg];
	else if (insetend(fmt, '+', 0))
		pfx = '+';
	else
		pfx = ' ';
	addprefix(&fixed, pfx);
	return (fixed);
}

static char	*flagchan2thesequel(int arg, char *fmt, char *res)
{
	if (insetend(fmt, '.', 0) && insetend("diuxX", fmt[arg], 0))
		res = field(res, 1, 1, ft_atoi(tnx(fmt, '.') + 1)
				+ (insetend("+ #", fmt[0], 0) || insetend(res, '-', 0))
				* (1 + insetend(fmt, '#', 0)));
	else
			res = field(res, !insetend(fmt, '-', 0), zeroflag(fmt) != NULL,
				ft_atoi(tnxnb(fmt)));
	if ((insetend(fmt, '#', 0) && insetend("xX", fmt[arg], 0)
			&& !(ft_strlen(res) == 1 && zeroflag(res) == res))
		|| ((insetend(fmt, ' ', 0) || insetend(fmt, '+', 0))
			&& fmt[arg] != 's'))
		res = prefix(arg, fmt, field(res, 1, zeroflag(fmt) != NULL,
					ft_strlen(res) + (ft_strlen(res) == ft_strlen(tnxhx(res))
						|| (ft_strlen(res) == 1 && zeroflag(res) == res))
					* (1 + insetend(fmt, '#', 0))));
	res = field(res, !insetend(fmt, '-', 0), zeroflag(fmt) != NULL,
			ft_atoi(tnxnb(fmt)));
	return (res);
}

char	*flagchan(int arg, char *fmt, char *res)
{
	if (insetend(fmt, '.', 0) && fmt[arg] == 's')
		return (field(res, !insetend(fmt, '-', 0),
				(-1 - ft_atoi(tnx(fmt, '.') + 1)),
				(tnx(fmt, '.') > tnxnb(fmt)) * ft_atoi(tnxnb(fmt))));
	if (insetend("123456789", fmt[0], 0) && fmt[arg] != 'c')
		res = field(res, 1, 0, ft_atoi(fmt));
	else if (fmt[arg] == 'c')
	{
		if (insetend(fmt, '-', 0))
			return (ft_strncpyfree(field(ft_strdup(""), 0, 0,
						ft_atoi(tnxnb(fmt))), res, 1));
		arg = res[0];
		free(res);
		res = field(ft_strdup(""), 0, 0, ft_atoi(tnxnb(fmt)));
		*(tnx(res, 0) - 1) = arg;
		return (res);
	}
	else
		res = flagchan2thesequel(arg, fmt, res);
	return (res);
}

/*
0# == #0
+0 == +
 0 == 0 
0+ == 0 then +

field > padding > prefix except for +0 where 0 is useless
no padding if left justify !!!

(inset(fmt, '0', fmt[arg]) && !inset("diouxX", fmt[arg], 0))
	|| ((inset(fmt, '+', fmt[arg]) || inset(fmt, ' ', fmt[arg]))
	&& !inset("di", fmt[arg], 0))
		if (insetend("123456789", fmt[0], 0))
		return (field(res, 1, 0, ft_atoi(fmt)));
	if ((insetend(fmt, '#', 0) && insetend("xX", fmt[arg], 0))
		|| ((insetend(fmt, ' ', 0) || insetend(fmt, '+', 0))
		&& insetend("di", fmt[arg], 0)))
		return (prefix(arg, fmt, field(res, 0, 0, ft_atoi(fmt)))); //fixme
	if (insetend(fmt, '-', 0))
		return (field(res, 0, 0, ft_atoi(++fmt)));
	else if (zeroflag(fmt) && insetend("diuxX", fmt[arg], 0))
		return (field(res, 1, 1, ft_atoi(++fmt)));
	"# +-0."
	cspdiuxX
	if (ljustify)
		while (res[++i])
			field[i] = res[i];
	else
		while (res[++i])
			field[minf - 1 - i] = res[i];
	|| (!insetend(fmt, '+', 0) && !insetend(fmt, '#', 0)
		&& !insetend(fmt, ' ', 0)))
	fl = -1;
	while (++fl < arg)
	{
		
		if (fmt[fl] == '#' && !zeroflag(fmt))//#
			res = prefix(arg - fl, &fmt[fl], field(res, rj, 0,
			 ft_strlen(res) + 2));
		else if (fmt[fl] == '#' && zeroflag(fmt))//0# & #0
			res = prefix(arg - fl, &fmt[fl], field(res, rj, 1,
			 ft_atoi(tonxtnbr(fmt))));
		if (fmt[fl] == ' ' && !zeroflag(fmt))//' '
			res = prefix(arg - fl, &fmt[fl], field(res, rj,
			0, ft_strlen(tonxtnbr(res))));
		else if (fmt[fl] == ' ' && zeroflag(fmt))// 0 & 0 
			res = prefix(arg - fl, &fmt[fl], field(res, rj, 1,
			 ft_atoi(tonxtnbr(fmt)) + 1));
		if (fmt[fl] == '+' && zeroflag(fmt) > &fmt[fl])//+ & +0
			res = prefix(arg - fl, &fmt[fl], field(res, rj,
			0, ft_atoi(tonxtnbr(fmt))));
		else if (fmt[fl] == '+' && zeroflag(fmt) < &fmt[fl])//0+
			res = prefix(arg - fl, &fmt[fl], field(res, rj,
			1, ft_atoi(tonxtnbr(fmt))));
		// else if (fmt[fl] == '0' && &fmt[fl] == zeroflag(fmt))
		// 	res = field(res, rj, fmt[0] != '+', ft_atoi(tonxtnbr(fmt)));
		
		// else if (fmt[fl] == '.')
		// 	res = ft_substr(res, 0, ft_atoi(tonxtnbr(&fmt[fl])));
		// else
		// 	tmp = res;
		// res = tmp;
	}
	else if (zeroflag(fmt))
	{
		res = field(res, 1, 1, ft_atoi(tonxtnbr(fmt)));
		if ((insetend(fmt, '#', 0) && insetend("xX", fmt[arg], 0))
		|| (insetend(fmt, ' ', 0) || insetend(fmt, '+', 0)))
			res = prefix(arg, fmt, field(res, 1, 0, ft_strlen(res) + 1
			 + insetend(fmt, '#', 0)));
	}
*/