#include "../Header/minishell.h"

t_toklist	*new_token(int nature, char *lexeme)
{
	t_toklist	*token;

	token = malloc(sizeof(t_toklist));
	if (!token)
		malloc_fail();
	token->nature = nature;
	token->lexeme = lexeme;
	token->next = NULL;
	return (token);
}

t_toklist	*new_io_token(t_lex *lex)
{
	if (lex->c == '<' && lex->string[lex->i + 1] == '<')
		return (new_token(_dchev, lex_strdup(lex, 2)));
	else if (lex->c == '<' && lex->string[lex->i + 1] != '<')
		return (new_token(_chev, lex_strdup(lex, 1)));
	else if (lex->c == '>' && lex->string[lex->i + 1] == '>')
		return (new_token(_dichev, lex_strdup(lex, 2)));
	else if (lex->c == '>' && lex->string[lex->i + 1] != '>')
		return (new_token(_ichev, lex_strdup(lex, 1)));
	return (NULL);
}

t_toklist	*get_tokens_list(t_lex *lex)
{
	t_toklist	*head;

	head = new_token(_head, NULL);
	while (lex->c)
	{
		if (ft_isblank(lex->c))
			lex_skip_blanks(lex);
		if (lex->c == '<' || lex->c == '>')
			lstadd_tok(&head, new_io_token(lex));
		else if (lex->c == '\'' || lex->c == '\"')
			lstadd_tok(&head, new_token(_word, lex_gather_str(lex)));
		else if (lex->c == '|')
			lstadd_tok(&head, new_token(_pipe, lex_strdup(lex, 1)));
		else if (lex->c)
			lstadd_tok(&head, new_token(_word, lex_gather_lexeme(lex)));
		lex_forward(lex);
	}
	return (head);
}
