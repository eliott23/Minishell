#include "m_shell.h"

int		ft_strcmp(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s2[i])
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		if (!s1[i] && !s2[i])
			return (1);
		return (0);
	}
	return (0);
}

int	m_parsing(char **av)
{
	char 	*x[] = {"export", "unset", "env", "cd", "pwd", "echo",0};
	int	i = 0;

	while (x[i] && !ft_strcmp(av[0], x[i]))
			i++;
	return (i);
}
