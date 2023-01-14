
#include "../../Header/minishell.h"

void	dollar_expanding(t_envl *envl, t_exp *s, char *in)
{
	char	*ptr;

	ptr = NULL;
	if (ft_isdigit(in[s->g_i + 1]))
		dollar_expanding_if_short(s, in);
	else
		dollar_expanding_else_short(envl, s, in);
}

void	dollar_expanding_if_short(t_exp *s, char *in)
{
	char	*ptr;

	ptr = NULL;
	s->g_i++;
	ptr = s->out;
	if (in[s->g_i] == '0')
	{
		s->out = ft_strjoin(s->out, "Minishell");
		free(ptr);
		ptr = s->out;
	}
	s->expa = get_until_dollar(&in[s->g_i + 1]);
	s->out = ft_strjoin(s->out, s->expa);
	free(ptr);
	s->g_i += ft_strlen(s->expa) + 1;
	free(s->expa);
}

void	dollar_expanding_else_short(t_envl *envl, t_exp *s, char *in)
{
	char	*ptr;

	ptr = NULL;
	ptr = s->out;
	s->expa = get_until_dollar(&in[s->g_i + 1]);
	s->out = ft_strjoin(s->out, get_env_var(envl, s->expa));
	free(ptr);
	s->g_i += ft_strlen(s->expa) + 1;
	free(s->expa);
}

void	dq_expanding(t_envl *envl, t_exp *s, char *in)
{
	char	*ptr;
	char	*ptr2;
	char	*ptr3;

	ptr = NULL;
	s->g_i++;
	ptr = s->out;
	s->expa = get_until_d_quote(&in[s->g_i]);
	if (ft_strlen(s->expa) > 0)
		ptr2 = expand_dq_sp(envl, s->expa);
	else
		ptr2 = ft_strdup("");
	ptr3 = char_at_start_end(ptr2, '\"');
	s->out = ft_strjoin(s->out, ptr3);
	free(ptr);
	free(ptr2);
	free(ptr3);
	s->g_i += ft_strlen(s->expa) + 1;
	free(s->expa);
}

void	sq_expanding(t_exp *s, char *in)
{
	int		size;
	char	*ptr;
	char	*ptr2;

	ptr = NULL;
	ptr2 = NULL;
	s->g_i++;
	size = get_until_s_quote(&in[s->g_i]);
	if (size > 0)
	{
		s->not_out = ft_substr(&in[s->g_i], 0, size);
		ptr2 = char_at_start_end(s->not_out, '\'');
	}
	else if (size == 0)
	{
		s->not_out = ft_strdup("");
		ptr2 = char_at_start_end(s->not_out, '\'');
	}
	ptr = s->out;
	s->out = ft_strjoin(ptr, ptr2);
	free(ptr);
	free(ptr2);
	s->g_i += ft_strlen(s->not_out) + 1;
	free(s->not_out);
}
