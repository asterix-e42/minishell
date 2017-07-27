/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 21:05:23 by ariard            #+#    #+#             */
/*   Updated: 2017/03/16 14:41:14 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			insert_newline(t_list **alst)
{
	t_token	*token;

	token = token_init();
	token->type = TK_NEWLINE;
	ft_lsteadd(alst, ft_lstnew(token, sizeof(*token)));
	free(token);
	return (0);
}
