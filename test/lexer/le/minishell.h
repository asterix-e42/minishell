
struct  s_data
{
	t_flag      opts;
	char        **av_data;
	char        *c_arg;
	int         fd;
	char        **env;
	int         argc;
	char        **argv;
	t_line      line;
	t_lexer     lexer;
	t_list      *fd_save[10];
	t_parser    parser;
	t_comp      *comp;
	t_exec      exec;
	t_jobc      jobc;
	char        **local_var;
	t_list      *lst_func;
	char        *binary;
};
