/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:13:35 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:25:39 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

void	i_heredoc(int *trigger, int *d, char **res)
{
	*trigger = 0;
	*res = NULL;
	signal(SIGINT, h_c);
	*d = dup(0);
}

void	f_heredoc(t_data *data, t_queue *limiters, char *s, char *res)
{
	signal(SIGINT, parent_ctlc);
	set_status(data, limiters, s, res);
}

int	fix_cd(t_ncd *ncd)
{
	if (ncd->old_pwd[0] == NULL)
	{
		free((ncd->t_oldpwd));
		(ncd->t_pwd) = getcwd((ncd->t_pwd), 0);
		(ncd->old_pwd)[0] = myft_strjoin("PWD=", (ncd->t_pwd));
		free((ncd->t_pwd));
		(ncd->old_pwd)[1] = 0;
		xprt(ncd->ev_h, ncd->x_ev_h, (ncd->old_pwd));
		freesplit((ncd->old_pwd));
		return (0);
	}
	return (1);
}
