/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 15:05:59 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/06 15:09:00 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>

int		is_dir(char *name)
{
	struct stat     a;

	if (lstat(name, &a) < 0)
		return (1);
	if (S_ISDIR(a.st_mode))
		return(0);
	return(2);
}

