/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:47:09 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/09 17:53:20 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
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
				writ = (writ < 1) ? 0 :ft_strrchr(*pwd, '/') - *pwd;
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

void	cd_next(char **av, char **env)
{
	char	*tmp;

	tmp = *(env + env_search("PWD", env));
	if (*(av))
	{
		if (*(av + 1))
			*(ft_strstr(tmp, *(av + 1)) - 1) = '\0';
		if (**(av) == '/')
			tmp = *(av);
		else
			tmp = ft_strjoini(tmp + 4, *(av), '/');
		pwd_short(&tmp);
		if (!*tmp && !(*(tmp + 1) = '\0'))
			*tmp = '/';
		env_add("PWD", tmp, &env);
	}
	chdir(tmp);
	free(tmp);
}	
