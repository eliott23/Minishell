#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av, char **ev)
{
	char	*arg[] = {0};
	int	id = fork();
	if (!id)
		execve("/bin/cat", NULL, NULL);
	else
		sleep(1);
}
