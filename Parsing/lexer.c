#include "../Header/minishell.h"

t_toklist	*lexer(char *cmd_line)
{
	t_lex		*lex;
	t_toklist	*tokens;

	lex = init_lex(cmd_line);
	tokens = get_tokens_list(lex);
	free(lex);
	return (tokens);
}
