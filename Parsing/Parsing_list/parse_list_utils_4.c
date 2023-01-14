#include "../../Header/minishell.h"

int	output_flag_case(t_prs_lst *p)
{
	p->red_out_flag = 1;
	if (p->tmp->next)
	{
		if (is_symbol(p->tmp->next->lexeme[0]))
			if (g_shell.prs_error == 0)
				error_printing();
		p->tmp = p->tmp->next;
		return (0);
	}
	else
	{
		if (g_shell.prs_error == 0)
			error_printing();
		return (-1);
	}
}

int	output_word_case(t_prs_lst *p)
{
	p->out_flag = 1;
	p->tmp_2->out_fd = open(p->tmp->lexeme, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (p->tmp_2->out_fd < 0)
	{
		if (g_shell.prs_error == 0)
			g_shell.prs_error = 1;
		putstr_fd(strerror(errno), 2);
		write(1, "\n", STDERR_FILENO);
		move_to_pipe(p);
		if (!p->tmp)
			return (-1);
	}
	p->red_out_flag = 0;
	if (p->tmp->next)
	{
		p->tmp = p->tmp->next;
		return (0);
	}
	else
		return (-1);
}

int	apnd_flag_case(t_prs_lst *p)
{
	p->apnd_flag = 1;
	if (p->tmp->next)
	{
		if (is_symbol(p->tmp->next->lexeme[0]))
			error_printing();
		p->tmp = p->tmp->next;
		return (0);
	}
	else
	{
		error_printing();
		return (-1);
	}
}

int	apnd_word_case(t_prs_lst *p)
{
	p->out_flag = 1;
	p->tmp_2->out_fd = open(p->tmp->lexeme, \
			O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (p->tmp_2->out_fd < 0)
	{
		if (g_shell.prs_error == 0)
			g_shell.prs_error = 1;
		putstr_fd("Minishell: ", 2);
		putstr_fd(p->tmp->lexeme, 2);
		putstr_fd(": ", 2);
		putstr_fd(strerror(errno), 2);
		putstr_fd("\n", 2);
		move_to_pipe(p);
	}
	p->red_in_flag = 0;
	if (p->tmp->next)
		p->tmp = p->tmp->next;
	else
		return (-1);
	return (0);
}

int	pipe_case(t_prs_lst *p)
{
	if (p->out_flag == 0 && (p->size -1 != p->tmp_2->idx))
		p->tmp_2->out_fd = -42;
	if (p->in_flag == 0 && (p->size - 1 != p->tmp_2->idx))
		p->tmp_2->in_fd = -42;
	if (p->tmp->next)
	{
		if (p->tmp->next->nature == _pipe)
		{
			error_printing();
			set_builtins_exit_status(258);
			return (-1);
		}
		pipe_init(p);
		p->tmp = p->tmp->next;
		p->tmp_2 = p->tmp_2->next;
		if (p->size - 1 == p->tmp_2->idx)
			p->tmp_2->in_fd = -42;
	}
	else
	{
		error_printing();
		set_builtins_exit_status(258);
		return (-1);
	}
	return (0);
}
