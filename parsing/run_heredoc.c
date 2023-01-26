/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:10:46 by hel-mefe          #+#    #+#             */
/*   Updated: 2023/01/26 22:27:19 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	limiter_found(t_data *data, t_queue **limiters, char **res, char *s)
{
	t_cmd	*cmd;
	char	*keep_res;

	cmd = get_command_by_id(data->commands, (*limiters)->cmd_id);
	if (cmd && cmd->has_heredoc && \
	(!(*limiters)->next || (*limiters)->next->cmd_id != cmd->cmd_id))
	{
		if ((*limiters)->ex)
		{
			keep_res = *res;
			*res = expand_result(data, *res);
			free(keep_res);
		}
		write(cmd->heredoc_pipe[1], *res, ft_strlen(*res));
		close(cmd->heredoc_pipe[1]);
	}
	if (*res)
		free(*res);
	(*limiters) = (*limiters)->next;
	*res = NULL;
	if (s)
		free(s);
}

void	limiter_not_found(char **res, char **s)
{
	*res = ft_strjoin_free(*res, *s);
	*res = ft_strjoin_free(*res, ft_strdup("\n"));
}

int	set_trigger(int *trigger)
{
	*trigger = 1;
	return (1);
}

void	set_status(t_data *data, t_queue *limiter, char *s, char *res)
{
	t_cmd	*cmd;

	cmd = get_command_by_id(data->commands, limiter->cmd_id);
	if (s)
		free(s);
	if (res)
		free(res);
	close(cmd->heredoc_pipe[1]);
}

int	run_heredoc(t_data *data, t_queue *limiters)
{
	char	*s;
	char	*res;
	int		trigger;
	int		d;

	trigger = 0;
	res = NULL;
	signal(SIGINT, h_C);
	d = dup(0);
	while (limiters)
	{
		gv.flag = 0;
		s = readline("haredoc> ");
		if (gv.flag && set_trigger(&trigger))
			break ;
		if (!s || !ft_strcmp(s, limiters->s))
			limiter_found(data, &limiters, &res, s);
		else
			limiter_not_found(&res, &s);
	}
	if (trigger)
	{
		set_status(data, limiters, s, res);
		dup2(d, 0);
		return (-1);
	}
	signal(SIGINT, parent_ctlC);
	return (0);
}
