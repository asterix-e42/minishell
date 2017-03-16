/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 01:32:13 by tdumouli          #+#    #+#             */
/*   Updated: 2016/12/12 01:59:42 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr(int n)
{
	int	i;

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		write(1, "-", 1);
		n = ~n + 1;
	}
	i = ft_intlen(n);
	while (--i != -1)
		ft_putchar(n / ft_power(10, i) % 10 + '0');
}
