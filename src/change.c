/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:19:35 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/21 01:45:20 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"
#include <stdlib.h>

int		copy(char **s, int symb, char *insert, int save_p)
{
	char	*tmp;

	tmp = *s;
	if (!(*s = ft_memalloc((1 + ft_strlen(*s) - save_p + ft_strlen(insert)))))
		return (1);
	ft_strncpy(*s, tmp, symb);
	ft_strcat(*s + symb, insert);
	ft_strcat(*s + symb + ft_strlen(insert), tmp + symb + save_p);
	free(tmp);
	return (0);
}

int		insert_home(char **s, int symb, char **env)
{
	char	*envhome;
	int		size;
	char	*tmp;

	tmp = *s;
	if (*(*s + symb) != '~')
		return (2);
	envhome = "";
	if (*(env + env_search("HOME", env)))
		envhome = *(env + env_search("HOME", env)) + 5;
	size = ft_strlen(envhome);
	if (!(*s = ft_memalloc((ft_strlen(tmp) + size + 1))))
		return (1);
	ft_strcpy(*s + symb, envhome);
	ft_strcat(*s + symb + size, tmp + symb + 1);
	free(tmp);
	tmp = NULL;
	return (0);
}

int		variable(char **s, int symb, char **env)
{
	int		save_p;
	char	save_c;
	char	*chang;
	int		ret;

	save_p = 2;
	if (*(*s + symb + 1) == '$' && (save_c = *(*s + symb + 2)) + 1)
		chang = ft_itoa(getpid());
	else
	{
		while (*(*s + symb + save_p) && *(*s + symb + ++save_p) != '$')
			save_c = *(*s + symb + save_p);
		*(*s + symb + save_p) = '\0';
		if (*(env + env_search(*s + symb + 1, env)))
			chang = ft_strdup(*(env + env_search(*s + symb + 1, env)) + save_p);
		else
			chang = ft_strdup("");
	}
	*(*s + symb + save_p) = save_c;
	copy(s, symb, chang, save_p);
	ret = ft_strlen(chang);
	free(chang);
	return (ret);
}
