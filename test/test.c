#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	main(int ac, char **av, char **ev)
{
	char	**arg = av + 1;
	int	id = 0;
	int	stat= 0;
	char *path  = av[1];
	if (!id)
	{
		if (access(path, F_OK))
		{
			printf("%s : command not found\n", path);	
			return (0);
		}
		if (access(path, X_OK))
		{
			printf("%s errno=%d\n", strerror(errno), errno);
			return (0);
		}
		execve(path, arg, NULL);
		return (0);
	}
	waitpid(id, &stat, 0);
}
