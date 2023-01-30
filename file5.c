/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:26:56 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:38:43 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

int	cd(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
	t_ncd	ncd;

	ncd.t_oldpwd = NULL;
	ncd.t_pwd = NULL;
	ncd.ev_h = ev_h;
	ncd.x_ev_h = x_ev_h;
	if (args && args[0])
	{
		if (!n_cd(&ncd, args))
			return (1);
	}
	return (0);
}

int	pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	is_an_option(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i] == 'n')
		i++;
	if (!str[i] && i > 1)
		return (1);
	return (0);
}

int	echo(char **args)
{
	int	i;
	int	n_l;

	i = 0;
	n_l = 1;
	if (args)
	{
		while (args[i] && is_an_option(args[i]))
		{
			n_l = 0;
			i++;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			i++;
			if (args[i])
				printf(" ");
		}
		if (n_l)
			printf("\n");
	}
	return (0);
}

void	handle_errors(char *cmd)
{
	int	fd;

	if (!cmd)
		exit(0);
	if (!cmd[0])
	{
		fprintf(stderr, "Minishell : %s : Command not found\n", cmd);
		exit(127);
	}
	fd = open(cmd, O_RDWR);
	if (fd < 0 && ft_srch(cmd, '/'))
	{
		fprintf(stderr, "%s : %s\n", cmd, strerror(errno));
		close(fd);
	}
	else if (ft_srch(cmd, '/'))
		fprintf(stderr, "%s : Command not found\n", cmd);
	exit(126);
}
