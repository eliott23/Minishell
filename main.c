/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:41:14 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:54:38 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

void	ft_close_pipes(int **pipes)
{
	int	i;

	i = 0;
	if (pipes)
	{
		while (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i++;
		}
	}
}

void	f_exec(int *stat, int id, t_nread *nread)
{
	ft_close_pipes((nread->pd)->pipes);
	waitpid(id, stat, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	ft_exit_status(*stat);
}

int	mini_hell(char **ev, int s0, int s1, t_nread nread)
{
	int		stat;
	t_cmd	*head;
	int		id;

	id = 0;
	init(ev, &(nread.ev_h), &(nread.x_ev_h));
	while (1)
	{
		pre_exec(0, &nread);
		if ((nread.pd)->n_cmds == 1)
			one_cmd(0, s0, s1, &nread);
		else
		{
			head = (nread.pd)->commands;
			signal(SIGINT, SIG_IGN);
			while (head)
			{
				m_cmds(0, &id, head, &nread);
				head = head->next;
			}
			f_exec(&stat, id, &nread);
			signal(SIGINT, parent_ctlc);
		}
	}
}

void	parent_ctlc(int i)
{
	i = 0;
	g_v.e_s = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **ev)
{
	t_nread	nread;
	int		s0;
	int		s1;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, parent_ctlc);
	s0 = dup(0);
	s1 = dup(1);
	g_v.e_s = 0;
	av = 0;
	(nread.str) = NULL;
	(nread.pd) = NULL;
	(nread.env) = NULL;
	(nread.main_env) = NULL;
	(nread.ev_h) = NULL;
	(nread.x_ev_h) = NULL;
	mini_hell(ev, s0, s1, nread);
	ac = 0;
}
