/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 22:36:14 by tdumouli          #+#    #+#             */
/*   Updated: 2017/04/13 22:49:11 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mini.h"
#include <stdlib.h>

void	ft_mini_exit(char **av, char ***env)
{
	env_free(env);
	if (av && *(av + 1))
		exit(ft_atoi(*(av + 1)));
	else
		exit(0);
}
