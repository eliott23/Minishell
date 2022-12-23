#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	main(int ac, char **av, char **ev)
{
	char	*arg[] = {"at", "est.c",0};
	int	id = fork();
	int	stat= 0;
	char *path  = "/bin/at";
	if (!id)
	{
		if (access(path, X_OK))
		{
			printf("%s\n", strerror(erno));
			return (0);
		}
		execve(path, arg, NULL);
		printf("%s: %s\n", arg[0],strerror(errno));
		return (0);
	}
	waitpid(id, &stat, 0);
}
