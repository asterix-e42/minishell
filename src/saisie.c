/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saisie.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 15:08:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/26 18:30:29 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include "mini.h"
#include "libft/include/libft.h"

int		ft_alloc(t_data *data, char *ajout)
{
	char	*tmp;

	tmp = data->str;
	if (ajout)
		data->len += ft_strlen(ajout);
	else
	{
		if (data->pointeur > 0 && --(data->pointeur) + 42)
			--(data->len);
		else
			return (0);
	}
	if (!(data->str = (char *)ft_memalloc(sizeof(char) * (data->len + 1))))
		return (-1);
	ft_strncpy(data->str, tmp, data->pointeur);
	if (ajout)
		ft_strcat(data->str, ajout);
	ft_strcat(data->str, tmp + data->pointeur + !(ajout));
	(data->pointeur) += (ajout) ? ft_strlen(ajout) : 0;
	*(data->str + data->len) = 0;
	free(tmp);
	return (0);
}

void	up(char *s, t_data *blk)
{
	if (*s == 27 && *(s + 1) == 91)
	{
		if (*(s + 2) == 65)
			;
		else if (*(s + 2) == 66)
			;
		else if (*(s + 2) == 67)
		{
			if (blk->pointeur < blk->len)
			{
				write(1, s, 3);
				++blk->pointeur;
			}
		}
		else if (*(s + 2) == 68)
		{
			if (blk->pointeur > 0)
			{
				write(1, s, 3);
				--blk->pointeur;
			}
		}
	}
}

char	*lecture(t_data *my_block)
{
	char	c[5];
	int		lec;

	*(c + 4) = 0;
	while ((lec = read(0, c, 4)) > 0)
	{
		if (*(c) == 10 || *c == 4)
			return (my_block->str);
		*(c + lec) = 0;
		if (lec == 3 && *c == 27)
			up(c, my_block);
		else if (31 < *c)
		{
			clean(my_block);
			if (*c == 127)
				ft_alloc(my_block, NULL);
			else
				ft_alloc(my_block, c);
			write(1, my_block->str, my_block->len);
			yolo(68, my_block->len - my_block->pointeur);
		}
	}
	return (my_block->str);
}

int		pass_canonique(struct termios	term)
{
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

char	*saisie(void)
{
	t_data			*my_block;
	struct termios	term;
	char			*read;

	if (!(my_block = t_dat_init()))
		return (NULL);
	if (tcgetattr(0, &term) == -1)
		return (NULL);
	if (pass_canonique(term))
		return (NULL);
	lecture(my_block);
	if (tcsetattr(0, 0, &term) == -1)
		return (NULL);
	read = my_block->str;
	free(my_block);
	return (read);
}
