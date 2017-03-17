/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grsa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:08 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/17 20:51:41 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/include/libft.h"
#include "mini.h"

char	*ft_strjoini(char const *s1, char const *s2, char c)
{
	char	*ret;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (i + j + 2))))
		return (NULL);
	*(ret + i + j + 1) = '\0';
	while (j--)
		*(ret + i + j + 1) = *(s2 + j);
	*(ret + i) = c;
	while (i--)
		*(ret + i) = *(s1 + i);
	return (ret);
}

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
			{
				insert_home((*s + j), i++, env);
			}
			else
				++i;
		}
		++j;
	}
}

int		new_process(char **av, char **env, char *error)
{
	pid_t	pid;
	int		count;

	if (!is_dir(*av))
	{
		cd(av, env);
		return (EXIT_SUCCESS);
	}
	if (!access(*av, X_OK))
	{
		pid = fork();
		if (pid == 0)
			execve(*av, av, env);
		else
			wait(&count);
		return(WEXITSTATUS (count));
	}
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(*av, 2);
	ft_putchar_fd('\n', 2);
	//write(1, "\x1b[31m", 6);
	return (1);
}

int		built_in(char **av, char ***env)
{
	char	*tmp[2];

	*(tmp + 1) = NULL;
	if (!ft_strcmp(*av, "cd"))
		cd(&(*(av + 1)), *env);
	else if (!ft_strcmp(*av, "setenv"))
	{
		if (!*(av + 1))
			env_print(*env);
		else if (!*(av + 2))
			env_add(*(av + 1), "''", env);
		else
			env_add(*(av + 1), *(av + 2), env);
	}
	else if (!ft_strcmp(*av, "env"))
		env_print(*env);
	else if (!ft_strcmp(*av, "unsetenv"))
		while (*(++av))
			env_sup(*av, env);
	else if (!ft_strcmp(*av, "echo"))
		if (!*(av + 1))
			write(1, "\n", 1);
		else
			while (*(++av))
				ft_putendl(*av);
	else
		return (0);
	while (*(av))
		++av;
	env_add("_", *(av - 1), env);
	return (1);
}

int			exe(char *argv, char ***env)
{
	char	**path;
	char	***av;
	int		i;
	char	*tmp;
	int		j;

	i = -1;
	if (supersplit(&av, argv, ';', ' '))
		return (0);
	while(*(av + ++i))
	{
		change((av + i), *env);
		env_add("_", **(av + i), env);
		if (built_in(*(av + i), env))
			;
		else if (ft_strchr(**(av + i), '/'))
			new_process(*(av + i), *env, " no such file or directory: ");
		else if ((path = ft_strsplit((*(*env + env_search("PATH", *env)) ?
				*(*env + env_search("PATH", *env)) + 5 :
		"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki"), ':')))
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
			new_process(*(av + i), *env, " command not found: ");
			freeteuse((void **)path, 1);
		}
	}
	//write(1, "r", 1);
	freeteuse((void **)av, 2);
	return (1);
}
