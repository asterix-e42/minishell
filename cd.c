/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 17:47:09 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/01 20:10:56 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"

void	pwd_short(char **pwd)
{
	int		writ;
	int		ber;

	writ = 0;
	ber = 0;
	while (*(*pwd + ber))
	{
		printf("ii%s\n", *pwd);
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
