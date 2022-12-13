/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 22:26:50 by aababach          #+#    #+#             */
/*   Updated: 2022/12/12 16:02:06 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// (opt == 0 ) --> count length ;
// ( opt == 1 ) --> skip sep ;

#include <stdlib.h>

int	ft_tools(char const *s, char c, int *i, int opt)
{
	int			len;
	int			temp;
	int			words;

	temp = *i;
	words = 0;
	len = 0;
	if (!opt)
	{
		while ((s + temp)[len] && (s + temp)[len] != c)
			len++;
	}
	if (opt)
	{
		while (s[*i] == c)
			(*i)++;
	}
	return (len);
}

int	ft_count_words(char const *s, char c)
{
	int	len;
	int	words;

	words = 0;
	len = 0;
	while (s[len])
	{
		if (s[len] != c && (!s[len + 1] || s[len + 1] == c))
			words++;
		len++;
	}
	return (words);
}

int	ft_fill(char **rslt, char const *s, int i, char c)
{
	int	a;
	int	b;
	int	len;

	a = 0;
	b = 0;
	while (a < ft_count_words(s, c))
	{
		b = 0;
		len = ft_tools(s, c, &i, 0);
		rslt[a] = malloc(sizeof(char) * (len + 1));
		if (!rslt[a])
			return (0);
		while (b < len)
		{
			rslt[a][b] = s[i];
			b++;
			i++;
		}
		rslt[a][b] = 0;
		ft_tools(s, c, &i, 1);
		a++;
	}
	rslt[a] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**rslt;

	i = 0;
	if (!s)
		return (0);
	ft_tools(s, c, &i, 1);
	rslt = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!rslt)
		return (0);
	if (!ft_fill(rslt, s, i, c))
		return (0);
	return (rslt);
}
