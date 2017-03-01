/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:09:48 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/01 16:25:00 by tdumouli         ###   ########.fr       */
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
	char	**env;
	char	**tmp;

	env = env_ralloc(0, environ);
	env_lvlup(env);
	printf("%s\n", *(env + 17));
	tmp = env;
	env_add("rATH", "dhSD", &env);
	sheel(av, env);
	return(0);
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

void sheel(char **s, char **env)
{
	char	*string;

	string = (char *)malloc(100);
	while (strcmp("exit", string))
	{
		write(1, "$> \x1b[39m", 8);
		get_next_line(0, &string);
		if (*(string))
			exe(string, env);
	}
}
