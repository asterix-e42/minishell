/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envie.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:31:38 by tdumouli          #+#    #+#             */
/*   Updated: 2017/04/12 13:15:23 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "mini.h"

void		env_free(char ***env)
{
	int count;

	count = -1;
	while (*(*env + ++count))
		free(*(*env + count));
	free(*env);
}

int			env_search(char *name, char **env)
{
	int count;

	count = 0;
	while (*(env + count) && ft_strcmp((char *)env[count], name) != '=')
		count++;
	return (count);
}

int			env_sup(char *name, char ***env)
{
	char	**new;
	int		lenght;
	int		size;

	if (**env)
	{
		size = -1;
		lenght = 0;
		while (*(*env + ++size))
			if (ft_strcmp((char *)(*env)[size], name) != '=')
				++lenght;
		new = (char **)malloc(sizeof(char *) * (lenght + 1));
		*(new + lenght) = NULL;
		while (--size != -1)
			if (ft_strcmp((char *)(*env)[size], name) != '=')
				*(new + --lenght) = *((*env) + size);
			else
				free(*((*env) + size));
		free(*env);
		*env = new;
	}
	return (0);
}

char		**env_ralloc(int diff, char **env)
{
	char	**new;
	int		lenght;

	lenght = -1;
	while (*(env + ++lenght))
		;
	if (!(new = (char **)malloc(sizeof(char *) * (lenght + diff + 1))))
		return (NULL);
	*(new + lenght + diff) = NULL;
	while (--lenght != -1)
		if ((*(new + lenght) = (char *)malloc(ft_strlen(*(env + lenght)))))
			*(new + lenght) = ft_strcpy(*(new + lenght), *(env + lenght));
		else
			return (NULL);
	return (new);
}

void		env_add(char *name, char *new, char ***env)
{
	int		where;
	char	**tmp;

	where = env_search(name, *env);
	if (!(*env)[where])
	{
		tmp = env_ralloc(1, *env);
		env_free(env);
		*env = tmp;
	}
	else
	{
		free(*(*env + where));
	}
	*(*env + where) = ft_strjoini(name, new, '=');
}
