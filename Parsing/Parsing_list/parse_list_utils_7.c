

#include "../../Header/minishell.h"

void	pipe_init(t_prs_lst *p)
{
	p->i = 0;
	p->out_flag = 0;
	p->in_flag = 0;
	p->apnd_flag = 0;
	p->first_word = 0;
	p->red_in_flag = 0;
	p->red_out_flag = 0;
	p->here_doc_flag = 0;
	g_shell.prs_error = 0;
}

int	gettingcounter(int current_token)
{
	if (current_token == _word)
		return (0);
	if (current_token == _chev || current_token == _ichev)
		return (2);
	if (current_token == _dchev || current_token == _dichev)
		return (2);
	return (-1);
}
