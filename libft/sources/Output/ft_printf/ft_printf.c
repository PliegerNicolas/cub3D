/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:09:21 by emis              #+#    #+#             */
/*   Updated: 2022/11/19 14:52:45 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	printarg(int lenarg, char *arg)
{
	int	i;

	i = -1;
	if (!arg)
	{
		lenarg = 6;
		arg = ft_strdup("(null)");
	}
	while (++i < lenarg)
		write(1, &arg[i], 1);
	free(arg);
	return (lenarg);
}

static char	*argtype(char c, va_list ap)
{
	if (c == 'c')
		return (strfrmchr((char) va_arg(ap, int)));
	else if (c == 's')
		return (strfrmstr(va_arg(ap, char *), 0));
	else if (c == 'p')
		return (strfrmptr(va_arg(ap, void *)));
	else if (c == 'd' || c == 'i')
		return (strfrmstr(ft_itoa(va_arg(ap, int)), 1));
	else if (c == 'u')
		return (strfrmstr(mknbr(va_arg(ap, unsigned int)), 1));
	else if (c == 'x')
		return (strfrmhex(va_arg(ap, int), 0));
	else if (c == 'X')
		return (strfrmhex(va_arg(ap, int), 1));
	else if (c == '%')
		return (strfrmchr('%'));
	else
		write(2, "Incorrect formatting with %", 27);
	return (NULL);
}

static int	format(char **fmt, va_list ap)
{
	int		i;
	char	*res;
	char	*trmfmt;

	i = -1;
	while (!insetend("cspdiuxX%", (*fmt)[++i], 0))
		;
	res = argtype((*fmt)[i], ap);
	if (!res || (*fmt)[i] == 0)
		return (printarg(0, res));
	if (!i)
		return (printarg(ft_strlen(res) * ((*fmt)[i] != 'c')
			+ ((*fmt)[i] == 'c'), res));
	trmfmt = ft_substr(*fmt, 0, i + 1);
	*fmt = *fmt + i;
	if (insetend("-0.# +", trmfmt[0], 0)
		|| insetend("123456789", trmfmt[0], 0))
		res = flagchan(i, trmfmt, res);
	free(trmfmt);
	if (*(*fmt) != 'c')
		return (printarg(ft_strlen(res), res));
	else
		return (printarg((ft_atoi(tnxnb(*fmt - i)) > 1)
				* (ft_atoi(tnxnb(*fmt - i)) - 1) + 1, res));
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start (ap, s);
	while (*s)
	{
		if (*s++ == '%')
			len += format((char **)(&s), ap);
		else if (++len)
			write(1, --s, 1);
		s++;
	}
	va_end(ap);
	return (len);
}

/*
//gcc ft_atoi.c ft_itoa.c ft_printf.c ft_printf_func.c ft_printf_util.c 
// ft_strdup.c ft_strlen.c libftprintf.h
#include <stdio.h>
#include <limits.h>

int	main() //int ac, char **av
{
	// if (ac > 1)
	// char	*str = "zobfesgsggegeg";
	// void	*ptr = str;

	// ft_printf("~chr %c~\n", 'c');
	// ft_printf("~str %s~\n", str);
	// ft_printf("~ptr %p~\n", ptr);
	// ft_printf("~dec %d~\n", 42);
	// ft_printf("~int %i~\n", 42);
	// ft_printf("~uni %u~\n", 42);
	// ft_printf("~hex %x~\n", 42);
	// ft_printf("~HEX %X~\n", 42);
	// ft_printf("~mod %%~\n");
	// ft_printf("~%%-10c: %-010c~\n", 'c');
	// ft_printf("~str %10s~\n", str);
	// ft_printf("~ptr %10p~\n", ptr);
	// ft_printf("~%%-+10d %-+10d~\n", 42);
	// ft_printf("~int %10i~\n", 42);
	// ft_printf("~uni %10u~\n", 42);
	// ft_printf("~HEX %10X~\n", 42);
	// ft_printf("~~~~~~~~~~~~~\nTesting real printf\n");
	// printf("%%-10c: %-10c~\n", 'e');
	// ft_printf("%%-+10d: %-+10d~\n", 42);
	// ft_printf("%%1d: %1d\n", 42);
	// ft_printf("%%1s: %1s\n", "Hello");
	// ft_printf("%%1.4s: %1.4s\n", "Hello");
	// ft_printf("%%-1.4s: %-1.4s\n", "Hello");
	// ft_printf("%%-1.20s: %-1.20s\n", "Hello");
	// ft_printf("%%-10x: %-10x\n", 42);
	// ft_printf("%%1s: %1s\n", "Hello");
	// ft_printf("%%.4s: %1.4s\n", "Hello");
	// ft_printf("%%-.4s: %-1.4s\n", "Hello");
	// ft_printf("%%-1.20s: %-1.20s\n", "Hello");
	
	// printf("me %d, lc %d\n", ft_printf("%c", 31), printf("%c", 31));
	printf("me %d, lc %d\n", 
	ft_printf("~.%-2c.%-2c.%-2c.%-2c.\n", 0, '1', 0, 0),
	printf("-.%-2c.%-2c.%-2c.%-2c.\n", 0, '1', 0, 0));
	printf("me %d, lc %d\n", ft_printf("~.%2c.%2c.%2c.\n", 0, '1', 0),
	printf("-.%2c.%2c.%2c.\n", 0, '1', 0));
	// printf("me %d, lc %d\n", ft_printf("%c", 0),
	// printf("%c", 0));
	// ft_printf("~%%s |%s %s %s~\n", "hi", "hello", "bonjour");
	// printf("me %d, lc %d\n", ft_printf("~%%s |%s %s %s~\n", "hi", "", ""),
	// printf("-%%s |%s %s %s~\n", "hi", "", ""));

	// ft_printf("~%%010u |%010u~\n", 42);
	// printf("-%%010u |%010u~\n", 42);

	// ft_printf("~%%#x |%#x~\n", 0);
	// printf("-%%#x |%#x\n", 0);
	// ft_printf("~%%0#10x |%0#10x~\n", 42);
	// printf("-%%0#10x |%0#10x\n", 42);
	// ft_printf("~%%#10x |%#10x~\n", 42);
	// printf("-%%#10x |%#10x\n", 42);
	// ft_printf("~%%#x |%#x~\n", 42);
	// printf("-%%#x |%#x\n", 42);

	// ft_printf("~%%+010d |%+10d~\n", -42);
	// printf("-%%+010d |%+10d~\n", -42);
	// ft_printf("~%%+010d |%+10d~\n", 42);
	// printf("-%%+010d |%+10d~\n", 42);
	// ft_printf("~%%0+10d |%0+10d~\n", 42);
	// printf("-%%0+10d |%0+10d~\n", 42);
	// ft_printf("~%%0+10d |%0+10d~\n", -42);
	// printf("-%%0+10d |%0+10d~\n", -42);
	// printf("%d/%d\n", ft_printf("~%%0 10d |%0 10d~\n", 42),
	// printf("-%%0 10d |%0 10d~\n", 42));
	// ft_printf("~%%0 10d |%0 10d~\n", -42);
	// printf("-%%0 10d |%0 10d~\n", -42);
	// ft_printf("~%% 010d |% 010d~\n", 42);
	// printf("-%% 010d |% 010d~\n", 42);
	// ft_printf("~%% 010d |% 010d~\n", -42);
	// printf("-%% 010d |% 010d~\n", -42);
	// ft_printf("~%%0 2d |%0 2d~\n", 42);
	// printf("-%%0 2d |%0 2d~\n", 42);
	// ft_printf("~%%0+2d |%0+2d~\n", 42);
	// printf("-%%0+2d |%0+2d~\n", 42);
	// ft_printf("~%%0+1d |%0+1d~\n", 42);
	// printf("-%%0+1d |%0+1d~\n", 42);

	// ft_printf("ayo %.13s~\n", "Hell0 world im bob");
	// // printf("ayu %.13s-\n", "Hell0 world im bob");
	// printf(" %d ", INT_MAX);
	// printf(" %d ", INT_MIN);
	// printf(" %d ", LONG_MAX);
	// printf(" %d ", LONG_MIN);
	// printf(" %d ", UINT_MAX);
	// printf(" %d ", ULONG_MAX);
	// ft_printf(" %d ", INT_MAX);
	// ft_printf(" %d ", INT_MIN);
	// ft_printf(" %d ", LONG_MAX);
	// ft_printf(" %d ", LONG_MIN);
	// ft_printf(" %d ", UINT_MAX);
	// ft_printf(" %d ", ULONG_MAX);

	// ft_printf("%%#10.4x %#10.4x .\n", 42);
	// printf("%%#10.4x %#10.4x .\n", 42);
	// ft_printf("%%#10.4d % 10.4d .\n", 42);
	// printf("%%#10.4d % 10.4d .\n", 42);
	// ft_printf("%%#10.4d % 10.4d .\n", -42);
	// printf("%%#10.4d % 10.4d .\n", -42);
	// ft_printf("%%05i %05i.\n", -15);
	// printf("%%05i %05i.\n", -15);
	// ft_printf("~%%#x |%#x~\n", 0);
	// printf("-%%#x |%#x\n", 0);
	// ft_printf("~%%#x |%#x~\n", -1);
	// printf("-%%#x |%#x\n", -1);
	// ft_printf("~%%#x |%#x~\n", 9);
	// printf("-%%#x |%#x\n", 9);
	// printf("-%%+d |%+d\n", 0);
	// printf("-%% d |% d\n", 0);

	// ft_printf(" %.s ", "-");
	// printf(" %.s ", "-");
	// ft_printf(" %.2s %.1s ", "", "-");
	// printf(" %.2s %.1s ", "", "-");
	// ft_printf(" %.3s %.2s ", " - ", "");
	// printf(" %.3s %.2s ", " - ", "");
	// ft_printf(" %.1s %.2s %.3s %.4s ", " - ", "", "4", "");
	// printf(" %.1s %.2s %.3s %.4s ", " - ", "", "4", "");

	// printf(" %014u \n", ULONG_MAX);
	// printf(" %015u \n", 9223372036854775807LL);
	// printf(" %09u %010u %011u %012u %013u %014u %015u\n",
	// INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// ft_printf(" %014u \n", ULONG_MAX);
	// ft_printf(" %015u \n", 9223372036854775807LL);
	// ft_printf(" %09u %010u %011u %012u %013u %014u %015u\n",
	// INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);

	// printf("%d, %d\n", printf(" %01x .\n", 0),
	// ft_printf(" %01x .\n", 0));
	// printf(" %+d. \n", 0);
	// ft_printf(" %+d. \n", 0);
	// //DOT for s
	// printf(" %.1s.\n", "");
	// printf("%.1s. \n", "");
	// printf(" %.2s.%.1s.\n", "", "-");
	// printf(" %.3s.%.2s.\n", " - ", "");
	// printf(" %.1s.%.2s.%.3s.%.4s.\n", " - ", "", "4", "");
	// ft_printf(" %.1s.\n", "");
	// ft_printf("%.1s. \n", "");
	// ft_printf(" %.2s.%.1s.\n", "", "-");
	// ft_printf(" %.3s.%.2s.\n", " - ", "");
	// ft_printf(" %.1s.%.2s.%.3s.%.4s.\n", " - ", "", "4", "");

	// ft_printf("%%#.4x %#.1x .\n", 42);
	// printf("%%#.4x %#.1x .\n", 42);
	// ft_printf("%%#.4d % .1d .\n", 4);
	// printf("%%#.4d % .1d .\n", 4);
	// ft_printf("%%#.4d % .1d .\n", -4);
	// printf("%%#.4d % .1d .\n", -4);
	// printf(" %.1d \n", 0);
	// ft_printf(" %.1d \n", 0);
	// printf(" %.2d \n", 1);
	// ft_printf(" %.2d \n", 1);
	// printf(" %.1d \n", 9);
	// ft_printf(" %.1d \n", 9);
	// printf(" %.2d \n", -1);
	// ft_printf(" %.2d \n", -1);
	
	// printf(".%s.\n", "bonsoir");
	// ft_printf(".%s.\n", "bonsoir");
	
}
*/