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
	char	*cd[] = {"cd", 0};
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
	id = fork();
	if (!id)
	{
		dup2(filedes[2], 1);
		execve("/usr/bin/grep", grep, NULL);
	}
	id = fork();
	if (!id)
	{
		dup2(filedes[1], 0);
		dup2(save, 1);
		// execve("/bin/ls", ls, NULL);
		execve("/bin/cat", cat, NULL);
		// close(filedes[2]);
		// close(save);
		// close(1);
		// sleep(34);
		exit(0);
	}
	waitpid(-1, &stat, 0);
	// while (i < 4)
	// {
	// id = fork();
	// if (!id)
	// {
	// 	if (i)
	// 	{
	// 		dup2(filedes[i - 1], 0);
	// 		fprintf(stderr, "duped i - 1 =%d on 0\n", i - 1);
	// 	}
	// 	if (i < 2)
	// 	{
	// 		dup2(filedes[i + 2], 1);
	// 		fprintf(stderr, "duped i + 2 =%d on 1\n", i + 2);
	// 	}
	// 	else
	// 	{
	// 		dup2(save, 1);
	// 		fprintf(stderr, "went heere at i=%d\n", i);
	// 	}
	// 	if (i == 0)
	// 		execve("/bin/cat", cat, NULL);
	// 	else
	// 		execve("/bin/ls", ls, NULL);
	// }
	// i += 2;
	// }
	waitpid(-1, &stat, 0);
}