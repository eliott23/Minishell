/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_funct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:05:09 by aababach          #+#    #+#             */
/*   Updated: 2023/01/29 18:23:07 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

void	read_prompt(t_ev *ev_h, t_nread *nread)
{
	signal(SIGINT, parent_ctlc);
	signal(SIGQUIT, SIG_IGN);
	if ((nread->str))
		free((nread->str));
	if ((nread->main_env))
		free_t_env((nread->main_env));
	if ((nread->env))
		freesplit((nread->env));
	if ((nread->pd))
		destory_data(&(nread->pd));
	(nread->str) = readline("Minishell>");
	while (!(nread->str) || !(nread->str)[0])
	{
		if (!(nread->str))
			exit(0);
		free((nread->str));
		(nread->str) = readline("Minishell>");
	}
	add_history((nread->str));
	(nread->main_env) = fill_env(ev_h);
	(nread->env) = ft_conv(ev_h);
	(nread->pd) = parse_line((nread->str), (nread->env), (nread->main_env));
	nread->t_errno = errno;
}

void	one_cmd(int v, int s0, int s1, t_nread *nread)
{
	signal(SIGINT, SIG_IGN);
	if (!(nread->pd)->commands->error_file)
	{
		v = m_parsing((nread->pd)->commands->main_args);
		if ((nread->pd)->commands->infile || (nread->pd)->commands->has_heredoc)
		{
			dup2((nread->pd)->commands->read_end, 0);
			close((nread->pd)->commands->read_end);
		}
		if ((nread->pd)->commands->outfile)
		{
			dup2((nread->pd)->commands->write_end, 1);
			close((nread->pd)->commands->write_end);
		}
		gv.e_s = what_to_call(v, &(nread->ev_h), \
		&(nread->x_ev_h), (nread->pd)->commands->main_args);
		dup2(s0, 0);
		dup2(s1, 1);
	}
	else
		error_one_cmd(nread);
	signal(SIGINT, parent_ctlc);
}

void	error_m_cmds(t_cmd *head, t_nread *nread)
{
	fprintf(stderr, "%s : %s\n", \
	head->error_file, strerror((nread->t_errno)));
	exit(1);
}

void	m_cmds(int v, int *id, t_cmd *head, t_nread *nread)
{
	(*id) = fork();
	if ((*id) == -1)
		exit(0);
	if (!(*id))
	{
		signal(SIGINT, SIG_DFL);
		if (!head->error_file)
		{
			if (head->cmd_id != 1 || head->infile || head->has_heredoc)
				dup2(head->read_end, 0);
			if (head->next || head->outfile)
				dup2(head->write_end, 1);
			ft_close_pipes((nread->pd)->pipes);
			v = m_parsing(head->main_args);
			if (!(head->is_builtin) || head->outfile)
				what_to_call(v + 1, \
						&(nread->ev_h), &(nread->x_ev_h), head->main_args);
			else
				exit(what_to_call(v, &(nread->ev_h), \
							&(nread->x_ev_h), head->main_args));
		}
		else
			error_m_cmds(head, nread);
	}
}

void	pre_exec(int hdoc, t_nread *nread)
{
	read_prompt((nread->ev_h), nread);
	hdoc = run_heredoc(nread->pd, (nread->pd)->heredoc);
	while (hdoc || !(nread->pd)->is_syntax_valid || (nread->pd)->err)
	{
		if (!hdoc && (!(nread->pd)->is_syntax_valid || (nread->pd)->err))
		{
			if ((nread->pd)->err)
				fprintf(stderr, "%s\n", (nread->pd)->err);
			gv.e_s = 258;
		}
		read_prompt((nread->ev_h), nread);
		hdoc = run_heredoc(nread->pd, (nread->pd)->heredoc);
	}
}
