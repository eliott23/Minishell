
#include "m_shell.h"
#include "include/parsing.h"

int	n_unset_h(t_ev **ev_h, char *str, t_ev *temp)
{
	if (ev_cmp(temp->var, str))
	{
		*ev_h = (*ev_h)->next;
		free(temp->var);
		free(temp);
		return (0);
	}
	return (1);
}

int	unset_h(t_ev **ev_h, char *str)
{
	t_ev	*temp;
	t_ev	*temp2;

	temp = *ev_h;
	if (temp)
	{
		if (!n_unset_h(ev_h, str, temp))
			return (0);
		while (temp->next)
		{
			if (ev_cmp(temp->next->var, str))
			{
				temp2 = temp->next;
				temp->next = temp->next->next;
				free(temp2->var);
				free(temp2);
				return (0);
			}
			temp = temp->next;
		}
	}
	return (0);
}

int	unset(t_ev **ev_h, t_ev **x_ev_h, char **args)
{
	int		i;
	int		v;
	char	*temp;
	int		r;

	i = 0;
	r = 0;
	if (args)
	{
		while (args[i])
		{
			v = v_exp(args[i], 1);
			if (v == 1)
			{
				unset_h(ev_h, args[i]);
				temp = x_ev_join(args[i]);
				unset_h(x_ev_h, temp);
				free(temp);
			}
			else
				r = 1;
			i++;
		}
	}
	return (r);
}

void	n_init(t_ev **temp, t_ev **temp2, t_ev **ev_h, t_ev **x_ev_h)
{
	*ev_h = malloc(sizeof(t_ev));
	*x_ev_h = malloc(sizeof(t_ev));
	*temp = *ev_h;
	*temp2 = *x_ev_h;
}

void	init(char **ev, t_ev **ev_h, t_ev **x_ev_h)
{
	int			i;
	t_ev		*temp;
	t_ev		*temp2;
	static char	*oldpwd[] = {"OLDPWD", 0};

	if (ev && ev[0] && ev_h)
	{
		i = 1;
		n_init(&temp, &temp2, ev_h, x_ev_h);
		temp->var = mft_strdup(ev[0]);
		temp2->var = x_ev_join(ev[0]);
		while (ev[i])
		{
			ev_alloc(temp, ev[i]);
			temp2->next = malloc(sizeof(t_ev));
			temp2->next->var = x_ev_join(ev[i]);
			temp = temp->next;
			temp2 = temp2->next;
			i++;
		}
		temp->next = NULL;
		temp2->next = NULL;
	}
	unset(ev_h, x_ev_h, oldpwd);
	xprt(ev_h, x_ev_h, oldpwd);
}