/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:26:59 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:54:38 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

int	nn_exec_h(t_nx *nx)
{
	while ((nx->paths)[(nx->i)])
	{
		(nx->path) = myft_strjoin((nx->paths)[(nx->i)], (nx->com));
		if (!access((nx->path), F_OK))
		{
			freesplit((nx->paths));
			if (!access((nx->path), X_OK))
				return (1);
			else
			{
				free((nx->path));
				g_v.e_s = 126;
				return (0);
			}
		}
		(nx->i)++;
		free((nx->path));
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
			(nx->path) = mft_strdup((nx->ev)->var + 5);
			(nx->paths) = ft_split((nx->path), ':');
			free((nx->path));
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
		ft_putstr_fd(STDERR_FILENO, build_error(ft_strdup("minishell: "), \
		ft_strdup(com + 1), \
		ft_strdup(": no such file or directory\n"), NULL), 1);
		g_v.e_s = 127;
		return (0);
	}
	if (access(com + 1, X_OK))
	{
		ft_putstr_fd(STDERR_FILENO, build_error(ft_strdup(com + 1), \
		ft_strdup(": "), ft_strdup(strerror(errno)), ft_strdup("\n")), 1);
		g_v.e_s = 126;
		return (0);
	}
	return (1);
}

char	*exec_h(t_ev *ev, char *com)
{
	t_nx	nx;
	int		r;

	nx.i = 0;
	nx.paths = NULL;
	nx.ev = ev;
	nx.com = com;
	r = n_exec_h(&nx);
	if (!r)
		return (0);
	else if (r == 1)
		return (nx.path);
	if (nx.paths)
		freesplit(nx.paths);
	if (ft_srch(com + 1, '/'))
	{
		if (!n2_exec_h(com))
			return (0);
		else
			return (mft_strdup(com + 1));
	}
	g_v.e_s = 127;
	ft_putstr_fd(STDERR_FILENO, build_error(ft_strdup("minishell: "), \
	ft_strdup(com + 1), ft_strdup(": command not found\n"), NULL), 1);
	return (0);
}

void	w_resetsig(int *stat, int id)
{
	waitpid(id, stat, 0);
	signal(SIGQUIT, SIG_IGN);
}
