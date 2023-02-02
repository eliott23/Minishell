#include "m_shell.h"
#include "include/parsing.h"

void	ft_putstr_fd(int fd, char *s, int free_bool)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	if (free_bool)
		free(s);
}

char	*build_error(char *s1, char *s2, char *s3, char *s4)
{
	char	*res;
	char	*kres;

	res = ft_strjoin(s1, s2);
	kres = res;
	res = ft_strjoin(res, s3);
	if (kres)
		free(kres);
	kres = res;
	res = ft_strjoin(res, s4);
	if (kres)
		free(kres);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
	return (res);
}
