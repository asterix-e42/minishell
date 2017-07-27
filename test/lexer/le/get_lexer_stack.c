/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lexer_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 17:39:45 by jhalford          #+#    #+#             */
/*   Updated: 2017/07/09 17:03:18 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_lexer_stack(t_lexer lexer)
{
	return (lexer.stack ? *(int*)lexer.stack->content : 0);
}
