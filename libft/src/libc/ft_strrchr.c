/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 03:09:00 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/01 18:32:47 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strrchr(const char *src, int s)
{
	char	*d;
	int		i;

	i = -1;
	d = (char *)src;
	while (*(++i + d) != '\0')
		if (*(i + d) == s)
		{
			d += i;
			i = 0;
		}
	if (s == '\0')
		return (d + i);
	if (*d != s)
		return (NULL);
	return (d);
}
