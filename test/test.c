#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av, char **ev)
{
	char	*arg[] = {"cat", 0};
	int	id = fork();
	if (!id)
		execve("/bin/cat", arg, NULL);
	else
		sleep(1);
}
