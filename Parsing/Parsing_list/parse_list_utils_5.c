

#include "../../Header/minishell.h"

int	args_case(t_prs_lst *p)
{
	p->tmp_2->args[p->i] = ft_strdup(p->tmp->lexeme);
	p->i++;
	if (p->tmp->next)
	{
		if (p->tmp->next->nature != _word)
		{
			p->tmp_2->args[p->i] = 0;
			p->tmp = p->tmp->next;
		}
		else
			p->tmp = p->tmp->next;
	}
	else
	{
		p->tmp_2->args[p->i] = 0;
		return (-1);
	}
	return (0);
}

int	here_doc_flag(t_prs_lst *p)
{
	p->here_doc_flag = 1;
	if (p->tmp->next)
	{
		if (is_symbol(p->tmp->next->lexeme[0]))
			error_printing();
		p->tmp = p->tmp->next;
	}
	else
	{
		error_printing();
		return (-1);
	}
	return (0);
}

int	here_doc_word(t_prs_lst *p)
{
	p->tmp_2->in_fd = ft_heredoc(p->tmp->lexeme);
	if (g_shell.here_sigint)
		return (stdin_keeper_hd());
	p->here_doc_flag = 0;
	p->in_flag = 1;
	if (p->tmp->next)
	{
		p->tmp = p->tmp->next;
		return (0);
	}
	else
		return (-1);
}

int	input_flag_case(t_prs_lst *p)
{
	p->red_in_flag = 1;
	if (p->tmp->next)
	{
		if (is_symbol(p->tmp->next->lexeme[0]))
		{
			error_printing();
			return (-1);
		}
		p->tmp = p->tmp->next;
		return (0);
	}
	else
	{
		error_printing();
		return (-1);
	}
}

int	input_word_case(t_prs_lst *p)
{
	p->tmp_2->in_fd = open(p->tmp->lexeme, O_RDONLY);
	p->in_flag = 1;
	if (p->tmp_2->in_fd < 0)
	{
		if (g_shell.prs_error == 0)
			g_shell.prs_error = 1;
		putstr_fd(strerror(errno), 2);
		putstr_fd("\n", 2);
		move_to_pipe(p);
		if (!p->tmp)
			return (-1);
		else
			return (0);
	}
	p->red_in_flag = 0;
	if (p->tmp->next)
	{
		p->tmp = p->tmp->next;
		return (0);
	}
	else
		return (-1);
}
