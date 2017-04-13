/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fenster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:09:48 by tdumouli          #+#    #+#             */
/*   Updated: 2017/04/13 22:48:47 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int		main(int ac, char **av, char **ae)
{
	char	***env;

	if (!(env = (char ***)malloc(sizeof(char **))))
		return (1);
	if (!(*env = env_ralloc(0, ae)))
		return (1);
	(void)ac;
	sheel(av, env);
	ft_mini_exit((void *)0, env);
}

void	sheel(char **av, char ***env)
{
	char	*string;
	int		flag;
	char	*tmp;

	whereareyou("PWD", env);
	env_add("_", *av, env);
	env_lvlup(env);
	flag = 1;
	while (flag)
	{
		write(1, "🦄 > \x1b[39m", 12);
		tmp = saisie();
		string = ft_strtrim(tmp);
		free(tmp);
		ft_putchar('\n');
		if (!string)
			;
		else if (!ft_strcmp("exit", string))
			flag = 0;
		else if (*(string))
			exe(string, env);
		free(string);
	}
}
