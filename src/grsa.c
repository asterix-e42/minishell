/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grsa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:08 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/21 02:43:07 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "mini.h"

void	change(char ***s, char **env)
{
	int i;
	int j;

	j = 0;
	while (*(*s + j))
	{
		i = 0;
		while (*(*(*s + j) + i))
		{
			if (*(*(*s + j) + i) == '$' && *(*(*s + j) + i + 1))
				i += variable((*s + j), i, env);
			else if (*(*(*s + j) + i) == '*')
				;
			else if (i == 0 && *(*(*s + j) + i) == '~')
				insert_home((*s + j), i++, env);
			else
				++i;
		}
		++j;
	}
}

int		new_process(char **av, char ***env, char *error)
{
	pid_t	pid;
	int		count;

	if (!is_dir(*av))
	{
		cd(*av, env);
		return (EXIT_SUCCESS);
	}
	if (!access(*av, X_OK))
	{
		pid = fork();
		if (pid == 0)
			execve(*av, av, *env);
		else
			wait(&count);
		return (WEXITSTATUS(count));
	}
	erreur(SHELL, error, *av);
	return (1);
}

int		built_in(char **av, char ***env)
{
	if (!*av)
		return (1);
	if (!ft_strcmp(*av, "cd"))
		built_cd(av, env);
	else if (!ft_strcmp(*av, "setenv"))
		ft_setenv(av, env);
	else if (!ft_strcmp(*av, "env"))
		env_print(*env);
	else if (!ft_strcmp(*av, "unsetenv"))
		while (*(++av))
			env_sup(*av, env);
	else if (!ft_strcmp(*av, "echo"))
		ft_echo(av);
	else
		return (0);
	while (*(av))
		++av;
	env_add("_", *(av - 1), env);
	return (1);
}

void	exe_path(char ***av, int i, char ***env)
{
	int		j;
	char	**path;
	char	*tmp;

	if ((path = ft_strsplit((*(*env + env_search("PATH", *env)) ?
						*(*env + env_search("PATH", *env)) + 5 : ""), ':')))
	{
		j = -1;
		while (*(path + ++j))
		{
			tmp = ft_strjoini(*(path + j), **(av + i), '/');
			if (!access(tmp, F_OK))
			{
				free(**(av + i));
				**(av + i) = tmp;
			}
			else
				free(tmp);
		}
		new_process(*(av + i), env, "command not found");
		freeteuse((void **)path, 1);
	}
}

int		exe(char *argv, char ***env)
{
	char	***av;
	int		i;

	i = -1;
	if (supersplit(&av, argv, ';', ' '))
		return (0);
	while (*(av + ++i))
	{
		change((av + i), *env);
		env_add("_", **(av + i), env);
		if (built_in(*(av + i), env))
			;
		else if (ft_strchr(**(av + i), '/'))
			new_process(*(av + i), env, "no such file or directory");
		else
			exe_path(av, i, env);
	}
	freeteuse((void **)av, 2);
	return (1);
}
