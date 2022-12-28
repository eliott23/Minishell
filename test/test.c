#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
void	putstr(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*arg = malloc(sizeof(char) * 10);
	int		save =  dup(1);
	// char	*cat[] = {NULL};
	char	*grep[] = {"grep", "a", NULL};
	char	*ls[] = {"ls", 0};
	int	id = 0;
	int	stat= 0;
	int	filedes[2];
	pipe(filedes);
	dup2(filedes[1], 1);
	id = fork();
	if (!id)
		execve("/bin/ls", ls, NULL);
	waitpid(-1, &stat, 0);
	// write(1, "ahahahac", 7);
	// printf("ahahaha\n");
	// exit(0);
	id = fork();
	if (!id)
	{
	dup2(filedes[0], 0);
	dup2(save, 1);
	execve("/usr/bin/grep", grep, NULL);
	// read(0, arg, 15);
	// printf("chhad l9lawi %s\n", arg);
	}
	waitpid(-1, &stat, 0);
}
