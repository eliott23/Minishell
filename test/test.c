#include <unistd.h>
#include <stdio.h>

int	main()
{
	char *buffer;

	buffer = NULL;
	chdir("");
	getcwd(buffer, 0);
	printf("%s\n", getcwd(buffer, 0));
}
