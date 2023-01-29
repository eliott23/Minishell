/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:59:52 by aababach          #+#    #+#             */
/*   Updated: 2023/01/29 17:02:26 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"

int	myft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i])
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		if (!s1[i] && !s2[i])
			return (1);
		return (0);
	}
	return (0);
}

int	m_parsing(char **av)
{
	static char	*x[] = {"export", \
		"unset", "env", "cd", "pwd", "echo", "exit", 0};
	int			i;

	i = 0;
	while (x[i] && !myft_strcmp(av[0], x[i]))
			i++;
	return (i);
}
