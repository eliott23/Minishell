

#include "../../Header/minishell.h"

char	*get_until_dollar(char *in)
{
	int		i;
	char	*out;

	i = 0;
	while (in[i])
	{
		if ((ft_isalnum(in[i]) == 0) && (in[i] != '_'))
		{
			if (!i)
				i++;
			break ;
		}
		i++;
	}
	out = ft_substr(in, 0, i);
	return (out);
}

int	get_until_s_quote(char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i] == '\'')
			break ;
		i++;
	}
	return (i);
}

char	*get_until_d_quote(char *in)
{
	int		i;
	char	*out;

	i = 0;
	while (in[i])
	{
		if (in[i] == '\"')
			break ;
		i++;
	}
	out = ft_substr(in, 0, i);
	return (out);
}

void	struct_init(t_exp *s)
{
	s->expa = NULL;
	s->not_out = NULL;
	s->out = NULL;
	s->g_i = 0;
}
