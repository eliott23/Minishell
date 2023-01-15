#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void	putstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

// int	main(int ac, char **av, char **ev)
// {
// 	char	*arg = malloc(sizeof(char) * 10);
// 	// int		save =  dup(1);
// 	char	*grep[] = {"grep", "a", NULL};
// 	char	*ls[] = {"ls", 0};
// 	char	*cat[] = {"cat", 0};
// 	char	*cd[] = {"cd", 0};
// 	char	*cata[] = {"cat", "a", 0};
// 	char	*echo[] = {"echo", "ahahahah", 0};
// 	int	id = 0;
// 	int	stat = 0;
// 	int	i = 0;
// 	int	t = 0;
// 	int	lim = 1;
// 	int	*filedes = malloc(sizeof(int) * (5));
// 	// filedes[0] = 0;
// 	while (t < 4)
// 	{
// 		pipe(filedes + 1 + t);
// 		t += 2;
// 	}
// 	// id = fork();
// 	// if (!id)
// 	// {
// 	// 	dup2(filedes[1], 1);
// 	// 	close (filedes[0]);
// 	// 	close (filedes[1]);
// 	// 	close(filedes[2]);
// 	// 	close(filedes[3]);
// 	// 	// execve("usr/bin/grep", grep, NULL);
// 	// 	execve("/bin/cat", cat, NULL);
// 	// 	exit(0);
// 	// }
// 	// id = fork();
// 	// if (!id)
// 	// {
// 	// 	dup2(filedes[0], 0);
// 	// 	dup2(filedes[3],1);
// 	// 	close (filedes[0]);
// 	// 	close (filedes[1]);
// 	// 	close(filedes[3]);
// 	// 	close(filedes[2]);
// 	// 	execve("/bin/cat", cat, NULL);
// 	// 	// execve("/bin/ls", ls, NULL);
// 	// 	exit(0);
// 	// }
// 	// id = fork();
// 	// if (!id)
// 	// {
// 	// 	dup2(filedes[2], 0);
// 	// 	close (filedes[0]);
// 	// 	close (filedes[1]);
// 	// 	close(filedes[3]);
// 	// 	close(filedes[2]);
// 	// 	// execve("/bin/cat", cat, NULL);
// 	// 	execve("/bin/ls", ls, NULL);
// 	// 	exit(0);
// 	// }
// 	// 	close (filedes[0]);
// 	// 	close (filedes[1]);
// 	// 	close(filedes[3]);
// 	// 	close(filedes[2]);
// 	// 	while (waitpid(-1, NULL, WUNTRACED) != -1);
// 	// else
// 	// {
// 	// }
// 	while (i < 6)
// 	{
// 	id = fork();
// 	if (!id)
// 	{
// 		if (i)
// 		{
// 			dup2(filedes[i - 1], 0);
// 			fprintf(stderr, "duped i - 1 =%d on 0\n", i - 1);
// 		}
// 		if (i < 4)
// 		{
// 			dup2(filedes[i + 2], 1);
// 			fprintf(stderr, "duped i + 2 =%d on 1\n", i + 2);
// 		}
// 		if (i == 0)
// 		{
// 			close(filedes[1]);	//needs to be dynamic;
// 			close(filedes[2]);	//needs to be dynamic;
// 			close(filedes[3]);	//needs to be dynamic;
// 			close(filedes[4]);	//needs to be dynamic;
// 			putstr("yarbi salama\n", 2);
// 			exit(0);
// 		}
// 		else if (i == 2)
// 		{
// 			close(filedes[1]);	//needs to be dynamic;
// 			close(filedes[2]);	//needs to be dynamic;
// 			close(filedes[3]);	//needs to be dynamic;
// 			close(filedes[4]);	//needs to be dynamic;
// 			execve("/bin/cat", cat, NULL);
// 		}
// 		else
// 		{
// 			// printf("it went here on i = %d\n", i);
// 			close(filedes[1]);	//needs to be dynamic;
// 			close(filedes[2]);	//needs to be dynamic;
// 			close(filedes[3]);	//needs to be dynamic;
// 			close(filedes[4]);	//needs to be dynamic;
// 			execve("/bin/ls", ls, NULL);
// 		}
// 	}
// 	i += 2;
// 	}
// 	close (filedes[1]);	//needs to be dynamic;
// 	close (filedes[2]);	//needs to be dynamic;
// 	close (filedes[3]);	//needs to be dynamic;
// 	close (filedes[4]);	//needs to be dynamic;
// 	while (waitpid(-1, NULL, WUNTRACED) != -1);
// }