#include "../Header/minishell.h"

void	lstadd_tok(t_toklist **lst, t_toklist *new_token)
{
	t_toklist	*current;

	if (new_token)
	{
		if (*lst)
		{
			current = *lst;
			while (current->next)
				current = current->next;
			current->next = new_token;
		}
		else
			*lst = new_token;
	}
}

void	print_tokens(t_toklist *tokens)
{
	t_toklist	*curr;

	curr = tokens;
	while (curr)
	{
		printf("(nature: %d, lexeme: %s)\n", curr->nature, curr->lexeme);
		curr = curr->next;
	}
}

int	toklist_size(t_toklist *tokens)
{
	t_toklist	*curr;
	int			i;

	i = 0;
	curr = tokens;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i - 1);
}
