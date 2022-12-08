#include "m_shell.h"

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
        if (s1[i] != '=' || (s2[i] != '=' && s2[i]))
            return (0);
        return (1);
    }
    return (0);
}

int	v_exp(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		if (!s[i])
			return (0);
		if ((s[i] >= 'a' && s[i] <= 'z') \
		|| (s[i] >= 'A' && s[i] <= 'Z')
		|| s[i] == '_')
			i++;
		else
			return (0);
		while (s[i] && s[i] != '=')
		{
			if ((s[i] >= '0' && s[i] <= '9') || \
			(s[i] >= 'a' && s[i] <= 'z') \
			|| (s[i] >= 'A' && s[i] <= 'Z')
			|| s[i] == '_')
				i++;
			else
				return (0);
		}
		if (s[i] == '=')
			return (-1);
		return (1);
	}
	return (0);
}

void	ev_alloc(t_ev *ev, char *var)
{
	ev->next = malloc(sizeof(t_ev));
	ev->next->var = ft_strdup(var);
}
