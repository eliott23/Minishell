/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 20:26:54 by aababach          #+#    #+#             */
/*   Updated: 2023/01/30 18:38:43 by aababach         ###   ########.fr       */
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
		printf("cd : %s: %s\n", \
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
				(ncd->OLD_PWD) = malloc(sizeof(char *) * 3);
				(ncd->OLD_PWD)[0] = myft_strjoin("OLDPWD=", (ncd->t_oldpwd));
				free((ncd->t_oldpwd));
				(ncd->t_pwd) = getcwd((ncd->t_pwd), 0);
				(ncd->OLD_PWD)[1] = myft_strjoin("PWD=", (ncd->t_pwd));
				free((ncd->t_pwd));
				(ncd->OLD_PWD)[2] = 0;
				xprt((ncd->ev_h), (ncd->x_ev_h), (ncd->OLD_PWD));
				freesplit((ncd->OLD_PWD));
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
	printf("cd: HOME not set\n");
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
			printf("cd : %s: %s\n", args[1], strerror(errno));
			free((ncd->t_oldpwd));
			return (0);
		}
		(ncd->OLD_PWD) = malloc(sizeof(char *) * 3);
		(ncd->OLD_PWD)[0] = myft_strjoin("OLDPWD=", (ncd->t_oldpwd));
		free((ncd->t_oldpwd));
		(ncd->t_pwd) = getcwd((ncd->t_pwd), 0);
		(ncd->OLD_PWD)[1] = myft_strjoin("PWD=", (ncd->t_pwd));
		free((ncd->t_pwd));
		(ncd->OLD_PWD)[2] = 0;
		xprt(ncd->ev_h, ncd->x_ev_h, (ncd->OLD_PWD));
		freesplit((ncd->OLD_PWD));
	}
	else
		cd_h(ncd->ev_h, ncd->x_ev_h);
	return (1);
}
