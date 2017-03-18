/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 15:29:31 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/18 21:52:39 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/include/libft.h"
#include "mini.h"

void erreur(char *error, char *what)
{
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(what, 2);
	ft_putchar_fd('\n', 2);
}

void	whereareyou(char *name, char ***env)
{
	char	tmp[1024];

	if (!getcwd(tmp, 1024))
		return ;
	env_add(name, tmp, env);
}

void	freeteuse(void **s, int niveau)
{
	int		i;

	i = -1;
	if (niveau)
		while (*(s + ++i))
			freeteuse((void **)*(s + i), niveau - 1);
	free(s);
	s = NULL;
}

int		supersplit(char ****ret, char *av, char s1, char s2)
{
	char	**e1;
	int		size;

	if (!(e1 = ft_strsplit(av, s1)))
		return (1);
	size = -1;
	while (*(e1 + ++size))
		;
	if (!(*ret = (char ***)malloc(sizeof(char **) * (size + 1))))
	{
		freeteuse((void **)e1, 1);
		return (1);
	}
	*(*ret + size) = NULL;
	while (--size + 1)
		if (!(*(*ret + size) = ft_strsplit(*(e1 + size), s2)))
		{
			while (*(*ret + ++size))
				freeteuse((void **)(*ret + size), 2);
			freeteuse((void **)e1, 1);
			return (1);
		}
	freeteuse((void **)e1, 1);
	return (0);
}
