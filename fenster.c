/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:09:48 by tdumouli          #+#    #+#             */
/*   Updated: 2017/02/26 21:27:03 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
extern char **environ;
int main(int ac, char **av)
{
	pid_t pid;

	printf("%s\n", *av);
	pid = fork();
	if (pid > 0)
		wait(0);
	else
		sheel(av);
}

void clean(char *s)
{
	pid_t pid;
	char **s1;

	s1 = (char **)malloc(sizeof(char *) * 2);
	*s1 = s;
	*(s1 + 1) = NULL;
	pid = fork();
	if (pid > 0)
		wait(0);
	else
		execve("/bin/ls", s1, NULL);
}

int cmd(char **string)
{
	int i;
	int y;

	i = 0;
	while((y = read(0, *string + (i * 10), 10)))
	{
		if (*(*string + (i * 10) + y - 1) == '\n')
			return (y - 1 + (i * 10));
		else
			++i;
				//realloc
	}
	return(0);
}

void sheel(char **s)
{
	char	*string;
	int		size;

	string = (char *)malloc(100);
	while (strcmp("exit", string))
	{
		write(1, "$> \x1b[39m", 8);
		size = cmd(&string);
		*(string + size) = '\0';
		exe(string);
//		write(1, string, size + 1);
	}
}
