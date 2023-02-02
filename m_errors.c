/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:28:28 by aababach          #+#    #+#             */
/*   Updated: 2023/02/02 13:28:30 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"
#include "include/parsing.h"

void	ft_putstr_fd(int fd, char *s, int free_bool)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	if (free_bool)
		free(s);
}

char	*build_error(char *s1, char *s2, char *s3, char *s4)
{
	char	*res;
	char	*kres;

	res = ft_strjoin(s1, s2);
	kres = res;
	res = ft_strjoin(res, s3);
	if (kres)
		free(kres);
	kres = res;
	res = ft_strjoin(res, s4);
	if (kres)
		free(kres);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
	return (res);
}

void	ihn(char **str, int caller, char *s)
{
	ft_putstr_fd(STDERR_FILENO, build_error(ft_strdup(str[caller]), \
	ft_strdup(": `"), ft_strjoin(s, "': not a valid identifier\n"), \
	0), 1);
}

void	ihn2(char **args)
{
	ft_putstr_fd(STDERR_FILENO, build_error(ft_strdup("cd : "), \
	ft_strdup(args[1]), ft_strdup(": "), ft_strjoin(strerror(errno), "\n")), 1);
}
