/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:31:10 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:50:34 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

char	*mft_strdup(const char *s1)
{
	char	*rtrn;
	size_t	len;
	size_t	i;

	i = 0;
	len = mft_strlen(s1);
	rtrn = malloc (sizeof(char) * len + 1);
	if (rtrn == NULL)
		return (0);
	while (i < len)
	{
		rtrn[i] = s1[i];
		i++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}

void	h_c(int i)
{
	i = 0;
	gv.e_s = 1;
	gv.flag = -2;
	write(1, "\n", 1);
	close(0);
}

void	error_one_cmd(t_nread *nread)
{
	fprintf(stderr, "%s : %s\n", \
	(nread->pd)->commands->error_file, \
	strerror((nread->t_errno)));
	gv.e_s = 1;
}
