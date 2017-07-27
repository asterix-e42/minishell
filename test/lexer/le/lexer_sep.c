/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:29:57 by jhalford          #+#    #+#             */
/*   Updated: 2017/05/01 18:52:34 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer_sep(t_list **alst, t_lexer *lexer)
{
	t_token	*token;
	char	c;
	char	cn;

	lexer->state = DEFAULT;
	token = (*alst)->content;
	if (token->type)
		return (lexer_lex(&(*alst)->next, lexer));
	c = lexer->str[lexer->pos];
	token_append(token, lexer, 0, 0);
	lexer->pos++;
	cn = lexer->str[lexer->pos];
	if (c == '&')
		token->type = cn == '&' ? TK_AND_IF : TK_AMP;
	else if (c == '|')
		token->type = cn == '|' ? TK_OR_IF : TK_PIPE;
	else if (c == ';')
		token->type = cn == ';' ? TK_DSEMI : TK_SEMI;
	else if (c == '!')
		token->type = TK_BANG;
	if (token->type == TK_AND_IF || token->type == TK_OR_IF
			|| token->type == TK_DSEMI)
		lexer->pos++;
	return (lexer_lex(&(*alst)->next, lexer));
}
