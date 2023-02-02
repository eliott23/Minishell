/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 01:05:18 by aababach          #+#    #+#             */
/*   Updated: 2023/01/22 22:37:24 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"

int	len(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		return (i);
	}
	return (0);
}

int	ev_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		if ((s1[i] != '=' && s1[i]) || (s2[i] != '=' && s2[i]))
			return (0);
		return (1);
	}
	return (0);
}

int	n_v_exp(char *s, int caller, char **str, int *i)
{
	if ((s[(*i)] >= 'a' && s[(*i)] <= 'z') \
	|| (s[(*i)] >= 'A' && s[(*i)] <= 'Z') || s[(*i)] == '_')
		(*i)++;
	else
	{
		if (caller != -1)
			ihn(str, caller, s);
		return (0);
	}
	while (s[(*i)] && s[(*i)] != '=')
	{
		if ((s[(*i)] >= '0' && s[(*i)] <= '9') || \
		(s[(*i)] >= 'a' && s[(*i)] <= 'z') \
			|| (s[(*i)] >= 'A' && s[(*i)] <= 'Z')
			|| s[(*i)] == '_')
			(*i)++;
		else
		{
			if (caller != -1)
				ihn(str, caller, s);
			return (0);
		}
	}
	return (1);
}

int	v_exp(char *s, int caller)
{
	int				i;
	static char		*str[3] = {"export", "unset", 0};

	i = 0;
	if (s)
	{
		if (!n_v_exp(s, caller, str, &i))
			return (0);
		if (s[i] == '=' && caller == 1)
		{
			if (caller != -1)
				ihn(str, caller, s);
			return (0);
		}
		return (1);
	}
	return (0);
}

void	ev_alloc(t_ev *ev, char *var)
{
	ev->next = malloc(sizeof(t_ev));
	ev->next->var = mft_strdup(var);
}
