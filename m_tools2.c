/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_tools2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:59:54 by aababach          #+#    #+#             */
/*   Updated: 2023/01/22 01:02:44 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"

void	n_x_ev_join(int *j, int *i)
{
	*j = 0;
	*i = 0;
}

char	*x_ev_join(char *s)
{
	int			i;
	int			j;
	static char	pref[12] = "declare -x \0";
	char		*res;

	if (!s)
		return (0);
	n_x_ev_join(&j, &i);
	res = malloc(sizeof(char) * (15 + len(s)));
	while (pref[i])
	{
		res[i] = pref[i];
		i++;
	}
	while (s[j] && s[j] != '=')
		res[i++] = s[j++];
	res[i++] = s[j];
	res[i++] = '"';
	if (s[j])
		j++;
	while (s[j])
		res[i++] = s[j++];
	res[i++] = '"';
	res[i] = 0;
	return (res);
}
