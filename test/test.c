#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	main(int ac, char **av, char **ev)
{
	char	*arg = malloc(sizeof(char) * 10);
	int	id = 0;
	int	stat= 0;
	int	filedes[2];
	pipe(filedes);
	dup2(filedes[1], 1);
	printf("ahahaha\n");
	id = fork();
	if (!id)
	{
		read(filedes[0], arg, sizeof(char) * 3);
		printf("%s\n", arg);
	}
	waitpid(-1, &stat, 0);
}
