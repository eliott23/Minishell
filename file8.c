/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:27:04 by aababach          #+#    #+#             */
/*   Updated: 2023/01/29 20:27:09 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

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
