/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:09:48 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/16 21:08:06 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char	**environ;

int		main(int ac, char **av)
{
	char	***env;

	(void)ac;
	if (!(env=(char ***)malloc(sizeof(char **))))
		return(1);
	*env = env_ralloc(0, environ);
	whereareyou("PWD", env);
	env_lvlup(env);
	env_add("_", *av, env);
	sheel(env);
	env_free(env);
	return (0);
}

void	sheel(char ***env)
{
	char	*string;

	while (42)
	{
		write(1, "$> \x1b[39m", 8);
		get_next_line(0, &string);
		if (!ft_strcmp("exit", string))
			exit(EXIT_SUCCESS);
		else if (*(string))
			exe(string, env);
	}
}
