/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:51:59 by emis              #+#    #+#             */
/*   Updated: 2022/11/27 12:47:42 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	append(char **str, char *toappend, int lenstr, int lenapn)
{
	char	*res;
	int		ret;

	ret = lenapn;
	if (lenapn <= 0)
		return (0);
	res = malloc(lenstr + lenapn + 1);
	if (!res)
		return (0);
	res[lenstr + lenapn] = 0;
	while (lenapn--)
		res[lenstr + lenapn] = toappend[lenapn];
	while (lenstr--)
		res[lenstr] = (*str)[lenstr];
	free((*str));
	*str = res;
	return (ret);
}

int	nxtbsn(char *buf, int bsize)
{
	int	i;

	i = -1;
	while (++i < bsize && buf && buf[i] != '\n' && buf[i])
		;
	return (i);
}

int	start_line(char **ln, char **buf)
{
	int		len;
	int		i;

	len = 0;
	while (*ln && (*ln)[len])
		len++;
	if (!len)
	{
		*ln = malloc(1);
		if (!(*ln))
			return (0);
		(*ln)[0] = 0;
	}
	if (!len || len == BUFFER_SIZE || (*ln)[nxtbsn(*ln, BUFFER_SIZE)] != '\n')
	{
		*buf = malloc(BUFFER_SIZE + 1);
		if (!(*buf))
			return (0);
		i = 0;
		while (i < BUFFER_SIZE + 1)
			(*buf)[i++] = 0;
	}
	else
		*buf = NULL;
	return (len);
}

char	*end_line(char **line)
{
	char	*trim;
	int		i;
	int		j;

	i = -1;
	while ((*line)[++i])
		if ((*line)[i] == '\n')
			break ;
	trim = malloc(i + 1 + ((*line)[i] == '\n'));
	if (!trim)
		return (NULL);
	i += ((*line)[i] == '\n');
	j = i;
	trim[j] = 0;
	while (i--)
		trim[i] = (*line)[i];
	while ((*line)[j + ++i])
		(*line)[i] = (*line)[j + i];
	(*line)[i] = 0;
	if (i == 0)
	{
		free(*line);
		*line = NULL;
	}
	return (trim);
}
