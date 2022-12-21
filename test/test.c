#include <unistd.h>
#include <stdio.h>

int	main()
{
	char *buffer;

	buffer = NULL;
	printf("%s\n", getcwd(NULL, 0));
}
