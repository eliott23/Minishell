/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:51:46 by aababach          #+#    #+#             */
/*   Updated: 2022/12/05 18:14:36 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"

int	ft_srch(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

size_t  ft_strlen(const char *s)
{
        size_t  i;

        i = 0;
        while (s[i])
                i++;
        return (i);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        size_t  len;
        char    *str;
        size_t  i;
        size_t  a;

        if (s1 == 0 || s2 == 0)
                return (0);
        a = 0;
        i = 0;
        len = ft_strlen(s1) + ft_strlen(s2);
        str = malloc(sizeof(char) * len + 1);
        if (!str)
                return (0);
        while (s1[i])
        {
                str[i] = s1[i];
                i++;
        }
        while (s2[a])
        {
                str[i + a] = s2[a];
                a++;
        }
        str[i + a] = 0;
        return (str);
}

char    *ft_strdup(const char *s1)
{
        char    *rtrn;
        size_t  len;
        size_t  i;

        i = 0;
        len = ft_strlen(s1);
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
