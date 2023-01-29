/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:26:49 by aababach          #+#    #+#             */
/*   Updated: 2023/01/29 20:27:12 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

void	xprt_e(t_ev **ev_h, char **args, int *i)
{
	t_ev	*temp;

	while (args[(*i)] && !v_exp(args[(*i)], -1))
		(*i)++;
	if (args[(*i)] && !(*ev_h))
	{
		*ev_h = malloc(sizeof(t_ev));
		(*ev_h)->var = mft_strdup(args[(*i)]);
		(*ev_h)->next = NULL;
		(*i)++;
	}
	if (args[(*i)])
	{
		if (v_exp(args[(*i)], -1))
		{
			temp = *ev_h;
			xprt_he(args[(*i)], temp);
		}
		(*i)++;
	}
}

int	xprt_hx(char *arg, t_ev *temp)
{
	while (temp)
	{
		if (ev_cmp(temp->var + 11, arg))
		{
			if (ft_srch(arg, '='))
			{
				free(temp->var);
				temp->var = x_ev_join(arg);
			}
			return (0);
		}
		if (!temp->next)
		{
			temp->next = malloc(sizeof(t_ev));
			temp->next->var = x_ev_join(arg);
			temp->next->next = NULL;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void	n_xprt_x(t_ev **x_ev_h, int *i, char **args)
{
	*x_ev_h = malloc(sizeof(t_ev));
	(*x_ev_h)->var = x_ev_join(args[(*i)]);
	(*x_ev_h)->next = NULL;
	(*i)++;
}

void	xprt_x(t_ev **x_ev_h, char **args, int *i, int *r)
{
	t_ev	*temp;
	int		t;

	t = *i;
	while (args[(*i)] && !v_exp(args[(*i)], 0))
		(*i)++;
	if (t != (*i))
		*r = 1;
	if (args[(*i)] && !(*x_ev_h))
		n_xprt_x(x_ev_h, i, args);
	if (args[(*i)])
	{
		if (v_exp(args[(*i)], 0))
		{
			temp = *x_ev_h;
			xprt_hx(args[(*i)], temp);
		}
		else
			*r = 1;
		(*i)++;
	}
}

int	xprt(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
	int	t;
	int	i;
	int	r;

	r = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_srch(args[i], '='))
		{
			t = i;
			xprt_x(x_ev_h, args, &i, &r);
			i = t;
			xprt_e(ev_h, args, &i);
		}
		else
			xprt_x(x_ev_h, args, &i, &r);
	}
	if (i == 0)
		env (*x_ev_h);
	return (r);
}
