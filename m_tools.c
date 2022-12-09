#include "m_shell.h"

int	len(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		return (i);
	}
	return(0);
}

int ev_cmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (s1 && s2)
    {
        while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
        {
            if (s1[i] != s2[i])
                return (0);
            i++;
        }
        if ((s1[i] != '=' && s1[i]) || (s2[i] != '=' && s2[i]))
            return (0);
        return (1);
    }
    return (0);
}

int	v_exp(char *s, int caller)
{
	int		i;
	static	char *str[3] = {"export", "unset", 0};

	i = 0;
	if (s)
	{
		if (!s[i])
		{
			printf("%s: `%s': not a valid identifier\n",str[caller], s);
			return (0);
		}
		if ((s[i] >= 'a' && s[i] <= 'z') \
		|| (s[i] >= 'A' && s[i] <= 'Z')
		|| s[i] == '_')
			i++;
		else
		{
			printf("%s: `%s': not a valid identifier\n",str[caller], s);
			return (0);
		}
		while (s[i] && s[i] != '=')
		{
			if ((s[i] >= '0' && s[i] <= '9') || \
			(s[i] >= 'a' && s[i] <= 'z') \
			|| (s[i] >= 'A' && s[i] <= 'Z')
			|| s[i] == '_')
				i++;
			else
			{
				printf("%s: `%s': not a valid identifier\n",str[caller], s);
				return (0);
			}
		}
		if (s[i] == '=' && caller)
		{
			printf("%s: `%s': not a valid identifier\n",str[caller], s);
			return (0);
		}
		return (1);
	}
	return (0);
}

void	ev_alloc(t_ev *ev, char *var)
{
	ev->next = malloc(sizeof(t_ev));
	ev->next->var = ft_strdup(var);
}

char	*x_ev_join(char *s)
{
	int		i;
	int			j;
	static char	pref[12]="declare -x ";
	char		*res;

	if (!s)
		return (0);
	j = 0;
	i = 0;
	res = malloc(sizeof(char) * (14 + len(s)));
	while (pref[i])
	{
		res[i] = pref[i];
		i++;
	}
	while (s[j] && s[j] != '=')
		res[i++] = s[j++];
	res[i++] = s[j++];
	res[i++] = '"';
	while (s[j])
		res[i++] = s[j++];
	res[i++] = '"';
	res[i] = 0;
	return (res);
}
