/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aababach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:31:10 by aababach          #+#    #+#             */
/*   Updated: 2023/01/22 22:37:24 by aababach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "m_shell.h"

char	*mft_strdup(const char *s1)
{
	char	*rtrn;
	size_t	len;
	size_t	i;

	i = 0;
	len = mft_strlen(s1);
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
