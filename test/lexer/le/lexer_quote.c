/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:07:08 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/17 20:16:30 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer_quote(t_list **alst, t_lexer *lexer)
{
	t_token		*token;

	token = (*alst)->content;
	token->type = token->type ? token->type : TK_WORD;
	if (lexer->str[lexer->pos] == '\'')
	{
		lexer->pos++;
		if (!(lexer->stack && *(int*)lexer->stack->content == QUOTE))
		{
			push(&lexer->stack, QUOTE);
			return (lexer_lex(alst, lexer));
		}
		lexer->state = WORD;
		pop(&lexer->stack);
		return (lexer_lex(alst, lexer));
	}
	token_append(token, lexer, 1, 1);
	lexer->pos++;
	return (lexer_lex(alst, lexer));
}
