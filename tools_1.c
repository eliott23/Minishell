/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:31:10 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:54:38 by aababach         ###   ########.fr       */
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
	g_v.e_s = 1;
	g_v.flag = -2;
	write(1, "\n", 1);
	close(0);
}

void	error_one_cmd(t_nread *nread)
{
	ft_putstr_fd(STDERR_FILENO, build_error(ft_strdup((nread->pd)->commands->error_file), ft_strdup(" : "), \
	ft_strdup(strerror(nread->t_errno)), ft_strdup("\n")), 1);
	// [ERROR_EDITED] - fprintf(stderr, "%s : %s\n", \
	(nread->pd)->commands->error_file, \
	strerror((nread->t_errno)));
	g_v.e_s = 1;
}
