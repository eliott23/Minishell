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
	int	id = 1;
	int	stat= 0;
	int	i = 0;
	int	t = 0;
	//create an array of intigers;
	int	filedes[8];
	while (i < 5)
	{
		if (id)
		{

		}
		id = fork();
		if (!id)
		{
			dup2(filedes[i], 0);
			//dup the prev pipe to 0;
			dup2(filedes[i + 1], 1); // vvariable
			execve("/bin/ls", ls, NULL);
			exit(0);
		}
		close(filedes[1]);
		close(1);
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
