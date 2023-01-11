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
	int	i = 0;
	int	t = 0;
	//create an array of intigers;
	int	filedes[8 + 1];
	filedes[0] = 0;
	while (t < 4)
	{
		pipe(filedes + 1 + t*2);
		t++;
	}
	while (i < 10)
	{
	id = fork();
	if (!id)
	{
		if (i)
			dup2(filedes[i], 0);
		if (i < 8)
			dup2(filedes[i + 1], 1);
		else
			dup2(save, 1);
		execve("/bin/ls", ls, NULL);
	}
	i += 2;
	}

	// id = fork();
	// if (!id)
	// {
	// 	dup2(filedes[2], 0);
	// 	dup2(save, 1);
	// 	execve("/usr/bin/grep", grep, NULL);
	// }
	// waitpid(-1, &stat, 0);
}
