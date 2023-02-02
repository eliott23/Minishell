/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:27:01 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:54:38 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

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
		return (g_v.e_s);
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
	signal(SIGQUIT, p_quit);
	free(com);
	if (!path)
		exit(g_v.e_s);
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
		printf("exit\n");
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
