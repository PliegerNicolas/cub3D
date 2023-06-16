/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:51:12 by emis              #+#    #+#             */
/*   Updated: 2022/11/27 12:15:31 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*list[4096];
	char		*buf;
	int			lenlin;
	int			rdv;

	lenlin = start_line(&list[fd], &buf);
	rdv = BUFFER_SIZE;
	if (buf)
	{
		while (rdv > 0 && buf[nxtbsn(buf, rdv)] != '\n')
		{
			rdv = read(fd, buf, BUFFER_SIZE);
			lenlin += append(&list[fd], buf, lenlin, rdv);
		}
		free(buf);
	}
	if (rdv >= 0 && lenlin)
		return (end_line(&list[fd]));
	free(list[fd]);
	list[fd] = NULL;
	return (NULL);
}

/*
#include <fcntl.h>
#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac > 1)
	{
		int fd1 = open(av[1], O_RDONLY);
		int fd2 = open(av[2], O_RDONLY);
		int fd3 = open(av[3], O_RDONLY);
		printf("what's up\n");
		char *s = get_next_line(fd1);
		printf("/1/%s", s);
		free(s);
		// printf("what's up\n");
		s = get_next_line(fd2);
		printf("/2/%s", s);
		free(s);
		s = get_next_line(fd3);
		printf("/3/%s", s);
		free(s);
		s = get_next_line(fd1);
		printf("/4/%s", s);
		free(s);
		s = get_next_line(fd2);
		printf("/5/%s", s);
		free(s);
		s = get_next_line(fd3);
		printf("/6/%s", s);
		free(s);
		s = get_next_line(fd1);
		printf("/7/%s", s);
		free(s);
		s = get_next_line(fd2);
		printf("/8/%s", s);
		free(s);
		s = get_next_line(fd3);
		printf("/9/%s", s);
		free(s);
		s = get_next_line(fd1);
		printf("/0/%s", s);
		free(s);
		// int a = start_line(&s, "hi\nhey\n");
		// printf("/%d:%s", a, s);
		// free(s);
		// printf("fd%d@%p\n", fd, current);
		// printf("list%p\nnext%p\n", *list, (*list)->next);
		// printf("%s.%s.%d\n", buf, list[fd], rdv);
	}
}
*/