/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:09:48 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/17 20:01:18 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char	**environ;

int		main(int ac, char **av)
{
	int retour;

	(void)ac;
	retour = sheel(av);
	while(1) ;
	exit(retour);
}

int		sheel(char **av)
{
	char	*string;
	char	***env;
	int		flag;

	if (!(env=(char ***)malloc(sizeof(char **))))
		return(1);
	*env = env_ralloc(0, environ);
	whereareyou("PWD", env);
	env_lvlup(env);
	env_add("_", *av, env);
	flag = 1;
	while (flag)
	{
		write(1, "$> \x1b[39m", 8);
		get_next_line(0, &string);
		if (!ft_strcmp("exit", string))
			flag = 0;
		else if (*(string))
			exe(string, env);
		free(string);
	}
	env_free(env);
	return(0);
}
