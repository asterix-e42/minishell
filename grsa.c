/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grsa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:08 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/11 02:48:52 by tdumouli         ###   ########.fr       */
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

void pre_exe(char **av, char **env)
{
	return ;
}

int		new_process(char **av, char **env, char *error)
{
	pid_t	pid;
	int		count;

	if (!is_dir(*av))
	{
		cd_next(av, env);
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
		cd_next(&(*(av + 1)), *env);
	else if (!ft_strcmp(*av, "setenv"))
	{
		if (!*(av + 1) && (*tmp = "/usr/bin/env"))
			new_process(tmp, *env, "merde");
		else if (!*(av + 2))
			env_add(*(av + 1), "''", env);
		else
			env_add(*(av + 1), *(av + 2), env);
	}
	else if (!ft_strcmp(*av, "unsetenv"))
		while (*(++av))
			env_sup(*av, env);
	else if (!ft_strcmp(*av, "echo"))
		while (*(++av))
			ft_putendl(*av);
	else
		return (0);
	while (*(av))
		++av;
	env_add("_", *(av - 1), env);
	return (1);
}

void freeteuse(void **s, int niveau)
{
	int i;

	i = -1;
	write(1, "1", 1);
	if (niveau)
		while (*(s + ++i))
			freeteuse((void **)*(s + i), niveau - 1);
	write(1, "2", 1);
	free(s);
	s = NULL;
	write(1, "3", 1);
}

int			supersplit(char ****ret, char *av, char s1, char s2)
{
	char	**e1;
	int		size;

	if (!(e1 = ft_strsplit(av, s1)))
		return (1);
	size = -1;
	while(*(e1 + ++size))
		;
	if (!(*ret = (char ***)malloc(sizeof(char **) * (size + 1))))
	{
		freeteuse((void **)e1, 1);
		return(1);
	}
	*(*ret + size) = NULL;
	while (--size + 1)
		if (!(*(*ret + size) = ft_strsplit(*(e1 + size), s2)))
		{
			while(*(*ret + ++size))
				freeteuse((void **)(*ret + size), 2);
			freeteuse((void **)e1, 1);
			return(1);
		}
	freeteuse((void **)e1, 1);
	return(0);
}

int			exe(char *argv, char ***env)
{
	char	**path;
	char	***av;
	int		i;

	if ((i = -1) && supersplit(&av, argv, ';', ' '))
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
			(--path);
			while (*(++path))
			{
				if (!access(ft_strjoini(*(path), **(av + i), '/'), F_OK))
				{
					free(**(av + i));
					**(av + i) = ft_strjoini(*(path), **(av + i), '/');
				}
				free(*path);
			}
			new_process(*(av + i), *env, " command not found: ");
		}
	}
	write(1, "1", 1);
	freeteuse((void **)av, 2);
	return (1);
}
