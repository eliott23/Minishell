

#include "../../Header/minishell.h"

void	dollar_white_space(t_exp *s, char *in)
{
	char	*ptr;

	ptr = NULL;
	ptr = s->out;
	s->not_out = get_until_dollar(&in[s->g_i]);
	s->out = ft_strjoin(ptr, s->not_out);
	free(ptr);
	s->g_i += ft_strlen(s->not_out);
	free(s->not_out);
}

void	dollar_ques_mark(t_exp *s, char *in)
{
	char	*ptr;
	char	*ptr2;

	(void)in;
	ptr = NULL;
	ptr2 = s->out;
	ptr = ft_itoa(g_shell.status);
	s->g_i++;
	s->out = ft_strjoin(ptr2, ptr);
	s->g_i++;
	free(ptr);
	free(ptr2);
}

void	expander_short(t_envl *envl, char *in, t_exp *s)
{
	while (in[s->g_i] != '\0')
	{
		if (in[s->g_i] == '$' && (in[s->g_i + 1] == '_'
				|| ft_isalnum(in[s->g_i + 1])))
			dollar_expanding(envl, s, in);
		else if (in[s->g_i] == '<' && in[s->g_i + 1] == '<')
			in_here_doc_handle(s, in);
		else if (in[s->g_i] == '$' && in[s->g_i + 1] == '?')
			dollar_ques_mark(s, in);
		else if (in[s->g_i] == '$' && !in[s->g_i + 1])
			dollar_only_case(s, in);
		else if (in[s->g_i] == '$' && (in[s->g_i + 1] == '\''
				|| in[s->g_i + 1] == '\"'))
			s->g_i++;
		else if (in[s->g_i] == '\"')
			dq_expanding(envl, s, in);
		else if (in[s->g_i] == '\'')
			sq_expanding(s, in);
		else if (in[s->g_i] == '$' && (in[s->g_i + 1] == ' '
				|| in[s->g_i + 1] == '\t'))
			dollar_white_space(s, in);
		else
			exp_else(s, in);
	}
}

char	*expander(t_envl *envl, char *in)
{
	t_exp	s;

	struct_init(&s);
	expander_short(envl, in, &s);
	return (s.out);
}

int	check_meta_char(char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if ((in[i] == '>') || (in[i] == '<') || (in[i] == '|'))
		{
			error_printing();
			return (-3);
		}
		else if (in[i] == ' ' || in[i] == '\t')
			i++;
		else
			break ;
	}
	return (0);
}
