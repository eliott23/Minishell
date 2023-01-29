/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:41:14 by aababach          #+#    #+#             */
/*   Updated: 2023/01/29 18:31:41 by aababach         ###   ########.fr       */
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

int	exec(char **args, t_ev *ev)
{
	char	*path;
	char	*com;
	int		id;
	int		stat;

	com = myft_strjoin("/", args[0]);
	if (!com)
		return (0);
	path = exec_h(ev, com);
	free(com);
	if (!path)
		return (gv.e_s);
	signal(SIGQUIT, p_quit);
	id = fork();
	if (!id)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve(path, args, ft_conv(ev));
		handle_errors(args[0]);
	}
	w_resetsig(&stat, id);
	if (path)
		free(path);
	return (ft_exit_status(stat));
}

int	ft_execp(char **args, t_ev *ev)
{
	char	*path;
	char	*com;

	com = myft_strjoin("/", args[0]);
	if (!com)
		exit(0);
	path = exec_h(ev, com);
	signal(SIGQUIT, p_quit); // handle sigquit
	free(com);
	if (!path)
		exit(gv.e_s);
	execve(path, args, ft_conv(ev));
	handle_errors(args[0]);
	return (0);
}

int	what_to_call(int v, t_ev **ev_h, t_ev **x_ev_h, char **args)
{
	if (v == 0)
		return (xprt(ev_h, x_ev_h, args + 1));
	else if (v == 1)
		return (unset(ev_h, x_ev_h, args + 1));
	else if (v == 2)
		return (env(*ev_h));
	else if (v == 3)
		return (cd(ev_h, x_ev_h, args));
	else if (v == 4)
		return (pwd());
	else if (v == 5)
		return (echo(args + 1));
	else if (v == 6)
	{
		fprintf(stderr, "exit\n");
		if (args && args[1])
			exit ((char)ft_atoi(args[1]));
		exit(0);
	}
	else if (v == 7)
		return (exec(args, *ev_h));
	else
		return (ft_execp(args, *ev_h));
	return (-1);
}

void	fdclose(int n, int *fd)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(fd[i]);
		i++;
	}
}

void	zero_fill(t_env *t)
{
	t->data = 0;
	t->name = 0;
	t->next = 0;
}

char	*ft_get_name(char *str)
{
	int		i;
	int		j;
	char	*r;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	r = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		r[j] = str[j];
		j++;
	}
	r[j] = 0;
	return (r);
}

char	*ft_get_data(char *str)
{
	int		i;
	char	*r;

	r = NULL;
	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		r = mft_strdup(&str[i + 1]);
	return (r);
}

void	free_t_env(t_env *ev)
{
	t_env	*t;

	while (ev)
	{
		free(ev->data);
		free(ev->name);
		t = ev;
		ev = ev->next;
		free(t);
	}
}

int	n_fill_env(t_ev *ev)
{
	int	i;

	i = 0;
	while (ev)
	{
		ev = ev->next;
		i++;
	}
	return (i);
}

t_env	*fill_env(t_ev	*ev)
{
	t_env	*r;
	t_env	*temp;
	int		j;
	int		i;

	i = n_fill_env(ev);
	j = 0;
	r = malloc(sizeof(t_env));
	zero_fill(r);
	temp = r;
	while (j < i)
	{
		r->data = ft_get_data(ev->var);
		r->name = ft_get_name(ev->var);
		if (j < i - 1)
		{
			r->next = malloc(sizeof(t_env));
			r = r->next;
			ev = ev->next;
		}
		else
			r->next = 0;
		j++;
	}
	return (temp);
}

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
	gv.e_s = 1;
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
	gv.e_s = 0;
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
