/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:51:46 by aababach          #+#    #+#             */
/*   Updated: 2023/01/20 20:32:40 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"

static void     ft_skip_signe(int *i, const char *str, int *s)
{
        if (str[*i] == '-' || str[*i] == '+')
        {
                if (str[*i] == '-')
                        *(s) *= -1;
                (*i)++;
        }
}

long long int   ft_atoi(const char *str)
{
        int                             i;
        int                             s;
        long long int   rslt;

        rslt = 0;
        s = 1;
        i = 0;
        while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
                i++;
        ft_skip_signe (&i, str, &s);
        while (str[i] >= '0' && str[i] <= '9')
        {
                rslt = rslt * 10 + str[i] - 48;
                i++;
        }
        if (str[i] && str[i] != 32)
                return (0);
        return (rslt * s);
}

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

char    *myft_strjoin(char const *s1, char const *s2)
{
        size_t  len;
        char    *str;
        size_t  i;
        size_t  a;

        if (!s1 || !s2)
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
