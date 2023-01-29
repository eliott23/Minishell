/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:26:46 by aababach          #+#    #+#             */
/*   Updated: 2023/01/29 20:27:12 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

void	p_quit(int i)
{
	i = 0;
	printf("Quit\n");
}

char	**ft_conv(t_ev *ev)
{
	char	**env;
	t_ev	*temp;
	int		i;

	temp = ev;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ev)
	{
		env[i] = mft_strdup(ev->var);
		i++;
		ev = ev->next;
	}
	env[i] = 0;
	return (env);
}

int	ft_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		gv.e_s = WEXITSTATUS(status);
		return (gv.e_s);
	}
	else if (WIFSIGNALED(status))
	{
		gv.e_s = status + 128;
		return (gv.e_s);
	}
	return (gv.e_s);
}

int	env(t_ev *ev_h)
{
	if (ev_h)
	{
		while (ev_h)
		{
			printf("%s\n", ev_h->var);
			ev_h = ev_h->next;
		}
	}
	return (0);
}

int	xprt_he(char *arg, t_ev *temp)
{
	while (temp)
	{
		if (ev_cmp(temp->var, arg) && ft_srch(arg, '='))
		{
			free(temp->var);
			temp->var = mft_strdup(arg);
			return (0);
		}
		if (!temp->next && ft_srch(arg, '='))
		{
			ev_alloc(temp, arg);
			temp->next->next = NULL;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
