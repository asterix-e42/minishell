/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:47:09 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/21 02:47:30 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"
#include "mini.h"

void	pwd_short(char **pwd)
{
	int		writ;
	int		ber;

	writ = 0;
	ber = 0;
	while (*(*pwd + ber))
	{
		if (*(*pwd + ber) == '/' && *(*pwd + ber + 1) == '.')
		{
			if (*(*pwd + ber + 2) == '.' &&
					(*(*pwd + ber + 3) == '/' || !*(*pwd + ber + 3)))
			{
				*(*pwd + writ) = '\0';
				writ = (writ < 1) ? 0 : ft_strrchr(*pwd, '/') - *pwd;
				ber += 3;
			}
			else if (*(*pwd + ber + 2) == '/' || !*(*pwd + ber + 2))
				ber += 2;
		}
		else
			*(*pwd + writ++) = *(*pwd + ber++);
	}
	*(*pwd + writ) = '\0';
	*(*pwd + writ - 1) = (*(*pwd + writ - 1) == '/') ? '\0' : (*pwd)[writ - 1];
}

char	*sesame(char *directory)
{
	struct stat		file_stat;

	if (stat(directory, &file_stat) < 0)
		return ("no such file or directory");
	else if (file_stat.st_mode & S_IXUSR)
		return (NULL);
	else
		return ("permission denied");
}

void	cd(char *av, char ***env)
{
	char	*tmp;

	whereareyou("PWD", env);
	tmp = *(*env + env_search("PWD", *env));
	if ((av))
	{
		if (*(av) == '/')
			tmp = ft_strdup((av));
		else if (*(tmp + 4) == '/' && !*(tmp + 5))
			tmp = ft_strjoini("", (av), '/');
		else
			tmp = ft_strjoini(tmp + 4, (av), '/');
		pwd_short(&tmp);
		if (!*tmp && !(*(tmp + 1) = '\0'))
			*tmp = '/';
		if (sesame(tmp))
			erreur("cd", sesame(tmp), av);
		else
		{
			whereareyou("OLDPWD", env);
			env_add("PWD", tmp, env);
			chdir(tmp);
		}
		free(tmp);
	}
}

void	built_cd(char **av, char ***env)
{
	if (!*(av + 1))
		;
	else if (!ft_strcmp(*(av + 1), "-"))
	{
		if (!*(*env + env_search("OLDPWD", *env)))
			erreur(SHELL, "cd:", "OLDPWD not set");
		else
			cd((*(*env + env_search("OLDPWD", *env)) + 7), env);
	}
	else
		cd((*(av + 1)), env);
}
