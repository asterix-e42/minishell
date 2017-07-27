/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:14:08 by ariard            #+#    #+#             */
/*   Updated: 2017/05/12 19:49:04 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_init(t_lexer *lexer)
{
	lexer->str = NULL;
	lexer->pos = 0;
	lexer->state = DEFAULT;
	lexer->stack = NULL;
	lexer->heredoc_stack = NULL;
}
