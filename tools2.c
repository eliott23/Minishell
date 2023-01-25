#include "m_shell.h"
#include "include/parsing.h"

void	h_C()
{
	printf("went here\n");
	gv.flag = -2;
	write(1, "\n", 1);
	close(0);
}
