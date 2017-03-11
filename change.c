/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 18:30:11 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/11 02:24:53 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "mini.h"
#include <stdlib.h>

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
	//ft_strncpy(*s, tmp, symb);
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
	char	*change;
	char	*tmp;

	save_p = 2;
	tmp = *s;
	if (*(*s + symb + 1) == '$' && (save_c = *(*s + symb + 2)) + 1)
		change = ft_itoa(getpid());
	else
	{
		while (*(*s + symb + save_p) && *(*s + symb + ++save_p) != '$')
			save_c = *(*s + symb + save_p + 1);
		*(*s + symb + save_p) = '\0';
		if ((change = "") && *(env + env_search(*s + symb + 1, env)))
			change = *(env + env_search(*s + symb + 1, env)) + save_p;
	}
	if (!(*s = ft_memalloc((1 + ft_strlen(*s) - save_p + ft_strlen(change)))))
		return (0);
	*(*s + symb + save_p) = save_c;
	ft_strncpy(*s, tmp, symb);
	ft_strcat(*s + symb, change);
	ft_strcat(*s + symb + ft_strlen(change), tmp + symb + save_p);
	free(tmp);
	return (ft_strlen(change));
}
