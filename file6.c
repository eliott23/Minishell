/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:26:59 by aababach          #+#    #+#             */
/*   Updated: 2023/01/29 20:27:12 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

int	nn_exec_h(t_nx *nx)
{
	while ((nx->PATHS)[(nx->i)])
	{
		(nx->PATH) = myft_strjoin((nx->PATHS)[(nx->i)], (nx->com));
		if (!access((nx->PATH), F_OK))
		{
			freesplit((nx->PATHS));
			if (!access((nx->PATH), X_OK))
				return (1);
			else
			{
				free((nx->PATH));
				gv.e_s = 126;
				return (0);
			}
		}
		(nx->i)++;
		free((nx->PATH));
	}
	return (-1);
}

int	n_exec_h(t_nx *nx)
{
	int	i;

	while ((nx->ev) && !ft_srch((nx->com) + 1, '/'))
	{
		if (ev_cmp((nx->ev)->var, "PATH"))
		{
			(nx->PATH) = mft_strdup((nx->ev)->var + 5);
			(nx->PATHS) = ft_split((nx->PATH), ':');
			free((nx->PATH));
			i = nn_exec_h(nx);
			if (i != -1)
				return (i);
		}
		(nx->ev) = (nx->ev)->next;
	}
	return (-1);
}

int	n2_exec_h(char *com)
{
	if (access(com + 1, F_OK))
	{
		fprintf(stderr, "minishell: %s: no such file or directory\n", com + 1);
		gv.e_s = 127;
		return (0);
	}
	if (access(com + 1, X_OK))
	{
		fprintf(stderr, "%s: %s\n", com + 1, strerror(errno));
		gv.e_s = 126;
		return (0);
	}
	return (1);
}

char	*exec_h(t_ev *ev, char *com)
{
	t_nx	nx;
	int		r;

	nx.i = 0;
	nx.PATHS = NULL;
	nx.ev = ev;
	nx.com = com;
	r = n_exec_h(&nx);
	if (!r)
		return (0);
	else if (r == 1)
		return (nx.PATH);
	if (nx.PATHS)
		freesplit(nx.PATHS);
	if (ft_srch(com + 1, '/'))
	{
		if (!n2_exec_h(com))
			return (0);
		else
			return (mft_strdup(com + 1));
	}
	gv.e_s = 127;
	fprintf(stderr, "minishell: %s: command not found\n", com + 1);
	return (0);
}

void	w_resetsig(int *stat, int id)
{
	waitpid(id, stat, 0);
	signal(SIGQUIT, SIG_IGN);
}
