
#include "minishell.h"
#include "lexer.h"
#include <unistd.h>

int main(int ac, char **av)
{
	t_list		**token;
	t_btree		**ast;
	char		*stream;

	stream = NULL;
	if (ac == 2)
	{
		do_lexer_routine(token, stream);
	}
	write(1, "done", 4);
}
