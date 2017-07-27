#include "minishell.h"
#include "lexer.h"

int str(char *str)
{
	ft_putstr(str);
	return(0);
}

void aff(t_lexer lexer)
{
	ft_lstiter(lexer.stack, str);
}



int		do_lexer_routine(t_list **token, char *stream)
{
	t_list				*ltoken;
	t_data				*data;
	static t_type		last;

	data = data_singleton();
	if (data->lexer.state == HEREDOC)
		ft_strappend(&data->lexer.str, (char[]){'\n', 0});
	if (data->parser.state == UNDEFINED && !isrw_delim(last))
		ft_strappend(&data->lexer.str, (char[]){';', 0});
	else if (data->parser.state == UNDEFINED && last != 0)
		ft_strappend(&data->lexer.str, (char[]){' ', 0});
	if (data->lexer.state == HEREDOC || (data->parser.state == UNDEFINED
		&& last != 0))
		data->lexer.pos++;
	ft_strappend(&data->lexer.str, stream);
	if (get_lexer_stack(data->lexer) == BACKSLASH)
		pop(&data->lexer.stack);
	ltoken = ft_lstlast(*token);
//	ft_putstr("1");
//		ft_putnbr(data->lexer.pos);
//	ft_putendl("1");
	if (lexer_lex(*token ? &ltoken : token, &data->lexer) < 0)
		exit(1);
	if ((get_lexer_stack(data->lexer) > 2) || (get_reserved_words(*token)))
		return (1);
	keep_last_type(&last, *token);
	data->lexer.state = DEFAULT;
//	ft_putstr("2");
//		aff(data->lexer);
//	ft_putendl("2");
//	ft_putstr("1");
//		ft_putstr(data->lexer.str);
//	ft_putstr("1");
	//ft_putstr(((t_lexer *)(*token)->content)->input);
	return (0);
}
