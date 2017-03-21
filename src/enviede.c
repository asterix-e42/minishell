/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviede.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 01:58:11 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/21 02:01:26 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include "libft.h"

void		env_lvlup(char ***env)
{
	int		where;
	char	*value;

	where = env_search("SHLVL", *env);
	if (!*(*env + where))
		value = ft_strdup("1");
	else
		value = ft_itoa(ft_atoi(*(*env + where) + 6) + 1);
	env_add("SHLVL", value, env);
	free(value);
}

void		env_print(char **env)
{
	--env;
	while (*(++env))
		ft_putendl(*env);
}
