/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:13:35 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:13:36 by aababach         ###   ########.fr       */
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