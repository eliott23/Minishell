#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

int is_regular_file(const char *path)
{
    struct stat path_stat;
	if (stat(path, &path_stat) == -1)
		printf("lol\n");
    return S_ISREG(path_stat.st_mode);
}
int	main(int ac, char **av, char **ev)
{
	printf("%d\n", is_regular_file("hh/a"));
}