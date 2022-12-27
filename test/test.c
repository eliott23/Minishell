#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int	main(int ac, char **av, char **ev)
{
	char	*arg = malloc(sizeof(char) * 10);
	// int		save =  dup(1);
	int		fd = open("hal3ar", O_CREAT | O_RDWR, 0777);
	char	*cat[] = {"cat", "test.c", 0};
	int	id = 0;
	int	stat= 0;
	int	filedes[2];
	pipe(filedes);
	dup2(fd, 1);
	// printf("ahahahasdcsdc\n");
	// write(1, "ahahaha", 7);
	// dprintf(1,"ahahaha");
	// exit(0);	
	id = fork();
	if (!id)
	{
	// dup2(filedes[0], 0);
	sleep(1);
	// read(fd, arg, 10);
	// fprintf(stderr, "%s\n", arg);
	exit(0);
	}
	waitpid(-1, &stat, 0);
}
