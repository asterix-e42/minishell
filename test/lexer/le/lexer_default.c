/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_default.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:36:21 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/17 19:28:09 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer_default(t_list **alst, t_lexer *lexer)
{
	t_token		*token;
	char		c;

	c = lexer->str[lexer->pos];
	if ((lexer->state = get_state_global(lexer)))
		return (lexer_lex(alst, lexer));
	if ((lexer->state = get_state_redir(lexer)))
		return (lexer_lex(alst, lexer));
	lexer->state = ft_isdigit(c) ? NUMBER : WORD;
	token = (*alst)->content;
	token->type = TK_WORD;
	return (lexer_lex(alst, lexer));
}
