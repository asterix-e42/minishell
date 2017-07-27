#include "minishell.h"

int			keep_last_type(t_type *last, t_list *token)
{
	t_list	*tmp;

	if (!(tmp = ft_lstlast(token)))
		return ((*last = 0));
	return (*last = ((t_token *)tmp->content)->type);
}
