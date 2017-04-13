/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saisie2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:32:04 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/24 17:40:40 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mini.h>

void	yolo(int dir, int y)
{
	char	depl[3];

	*(depl) = 27;
	*(depl + 1) = 91;
	*(depl + 2) = dir;
	while (--y > -1)
		write(1, depl, 3);
}

void	clean(t_data *blk)
{
	char	c;
	int		i;

	i = blk->len;
	c = 127;
	yolo(68, blk->pointeur);
	while (--i > -1)
		write(1, &c, 1);
	yolo(68, blk->len);
}

t_data	*t_dat_init(void)
{
	t_data	*ret;

	if (!(ret = malloc(sizeof(t_data))))
		return (NULL);
	if (!(ret->str = malloc(sizeof(char))))
	{
		free(ret);
		return (NULL);
	}
	*(ret->str) = 0;
	ret->len = 0;
	ret->pointeur = 0;
	return (ret);
}
