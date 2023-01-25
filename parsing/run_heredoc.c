/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:10:46 by hel-mefe          #+#    #+#             */
/*   Updated: 2023/01/25 22:56:13 by aababach         ###   ########.fr       */
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
	printf("triggered\n");
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
	printf("set_status\n");
	close(cmd->heredoc_pipe[1]);
}

int	run_heredoc(t_data *data, t_queue *limiters)
{
	char	*s;
	char	*res;
	int		trigger;

	trigger = 0;
	res = NULL;
	signal(SIGINT, h_C);
	// handle_signals(2);
//	g_global.new = dup(0);
	while (limiters)
	{
		gv.flag = 0;
		s = readline("haredoc> ");
		if (gv.flag && set_trigger(&trigger))
		{
			printf("broke");
			break ;
		}
		if (!s || !ft_strcmp(s, limiters->s))
		{
			limiter_found(data, &limiters, &res, s);
			printf("went here\n");
		}
		else
			limiter_not_found(&res, &s);
	}
	if (trigger)
	{
		printf("went here\n");
		set_status(data, limiters, s, res);
		return (-1);
	}
	return (0);
	//dup2(g_global.new, 0);
}
