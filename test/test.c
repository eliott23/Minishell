#include <unistd.h>

int	main()
{
	char *buffer;

	buffer = NULL;
	chdir("/..");
	printf("%s\n", getcwd(buffer, 1024));
}
