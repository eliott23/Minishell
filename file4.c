/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:26:54 by aababach          #+#    #+#             */
/*   Updated: 2023/02/01 21:34:47 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

void	freesplit(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			free(s[i]);
			i++;
		}
		free(s);
	}
}

int	nn_cd_h(t_ncd *ncd)
{
	if ((ncd->t) == -1)
	{
		fprintf(stderr, "cd : %s: %s\n", \
				&(ncd->temp)->var[(ncd->i) + 1], strerror(errno));
		free((ncd->t_oldpwd));
		return (0);
	}
	return (1);
}

int	n_cd_h(t_ncd *ncd)
{
	if (ev_cmp((ncd->temp)->var, "HOME"))
	{
		while ((ncd->temp)->var[ncd->i])
		{
			if ((ncd->temp)->var[ncd->i] == '=')
			{
				(ncd->t_oldpwd) = getcwd((ncd->t_oldpwd), 0);
				(ncd->t) = chdir(&(ncd->temp)->var[(ncd->i) + 1]);
				if (!nn_cd_h(ncd))
					return (0);
				(ncd->old_pwd) = malloc(sizeof(char *) * 3);
				(ncd->old_pwd)[0] = myft_strjoin("OLDPWD=", (ncd->t_oldpwd));
				free((ncd->t_oldpwd));
				(ncd->t_pwd) = getcwd((ncd->t_pwd), 0);
				(ncd->old_pwd)[1] = myft_strjoin("PWD=", (ncd->t_pwd));
				free((ncd->t_pwd));
				(ncd->old_pwd)[2] = 0;
				xprt((ncd->ev_h), (ncd->x_ev_h), (ncd->old_pwd));
				freesplit((ncd->old_pwd));
				return (0);
			}
			(ncd->i)++;
		}
	}
	return (1);
}

int	cd_h(t_ev **ev_h, t_ev **x_ev_h)
{
	t_ncd	ncd;

	ncd.t_oldpwd = NULL;
	ncd.t_pwd = NULL;
	ncd.i = 0;
	ncd.temp = *ev_h;
	ncd.ev_h = ev_h;
	ncd.x_ev_h = x_ev_h;
	while (ncd.temp)
	{
		if (!n_cd_h(&ncd))
			return (0);
		ncd.temp = ncd.temp->next;
	}
	ft_putstr_fd(STDERR_FILENO, "cd: HOME not set\n", 0);
	return (0);
}

int	n_cd(t_ncd *ncd, char **args)
{
	if (args[1])
	{
		(ncd->t_oldpwd) = getcwd((ncd->t_oldpwd), 0);
		(ncd->t) = chdir(args[1]);
		if ((ncd->t) == -1)
		{
			ft_putstr_fd(STDERR_FILENO, build_error(ft_strdup("cd : "), \
			ft_strdup(args[1]), ft_strdup(": "), ft_strjoin(strerror(errno), "\n")), 1);
			// fprintf(stderr, "cd : %s: %s\n", args[1], strerror(errno)); [ERROR_EDITED]
			free((ncd->t_oldpwd));
			return (0);
		}
		(ncd->old_pwd) = malloc(sizeof(char *) * 3);
		(ncd->old_pwd)[0] = myft_strjoin("OLDPWD=", (ncd->t_oldpwd));
		if (!fix_cd(ncd))
			return (1);
		free((ncd->t_oldpwd));
		(ncd->t_pwd) = getcwd((ncd->t_pwd), 0);
		(ncd->old_pwd)[1] = myft_strjoin("PWD=", (ncd->t_pwd));
		free((ncd->t_pwd));
		(ncd->old_pwd)[2] = 0;
		xprt(ncd->ev_h, ncd->x_ev_h, (ncd->old_pwd));
		freesplit((ncd->old_pwd));
	}
	else
		cd_h(ncd->ev_h, ncd->x_ev_h);
	return (1);
}
