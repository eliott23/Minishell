#include "../Header/minishell.h"

void	t_parser_init(t_parser *p)
{
	p->red_line = NULL;
	p->out = NULL;
	p->tokens = NULL;
	p->cmd_line = NULL;
	p->error_code = 0;
}

int	parser_short(t_parser *p)
{
	p->out = p->red_line;
	p->red_line = expander(g_shell.env, p->out);
	p->tokens = lexer(p->red_line);
	free(p->out);
	free(p->red_line);
	p->cmd_line = parse_list(p->tokens->next, g_shell.env);
	free_token_list(p->tokens);
	return (0);
}
