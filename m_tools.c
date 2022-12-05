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

void	ev_alloc(t_ev *ev, char *var)
{
	ev->next = malloc(sizeof(t_ev));
	ev->next->var = ft_strdup(var);
}
