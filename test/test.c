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
	char	*grep[] = {"grep", "a", NULL};
	char	*ls[] = {"ls", 0};
	char	*cat[] = {"cat", 0};
	char	*cata[] = {"cat", "a", 0};
	char	*echo[] = {"echo", "ahahahah", 0};
	int	id = 0;
	int	stat = 0;
	int	i = 0;
	int	t = 0;
	int	*filedes = malloc(sizeof(int) * 3);
	filedes[0] = 0;
	while (t < 2)
	{
		pipe(filedes + 1 + t);
		t += 2;
	}
	// id = fork();
	// if (!id)
// {	
	// dup2(filedes[2], 1);
	// execve("/bin/cat", cat, NULL);
	// exit(0);
// }
// dup2(filedes[1], 0);
	// execve("/bin/cat", cat, NULL);
	t = 0;
	while (i < 4)
	{
	id = fork();
	if (!id)
	{
		if (i)
			dup2(filedes[i - 1], 0);
		if (i < 2)
		{
			dup2(filedes[i + 2], 1);
			fprintf(stderr, "went here at i=%d\n", i);
		}
		else
		{
			dup2(save, 1);
			fprintf(stderr, "went heere at i=%d\n", i);
		}
		if (i == 0)
			execve("/bin/cat", cat, NULL);
		// fprintf(stderr, "%d\n", i;
			// execve("/bin/ls", ls, NULL);
		else
			execve("/bin/cat", cat, NULL);
		exit(0);
	}
	sleep(1);
	i += 2;
	}
	waitpid(-1, &stat, 0);

	// id = fork();
	// if (!id)
	// {
	// 	dup2(filedes[2], 0);
	// 	dup2(save, 1);
	// 	execve("/usr/bin/grep", grep, NULL);
	// }
	// waitpid(-1, &stat, 0);
}
