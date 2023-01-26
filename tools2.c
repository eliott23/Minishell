#include "m_shell.h"
#include "include/parsing.h"

void	h_C()
{
	gv.e_s = 1;
	gv.flag = -2;
	write(1, "\n", 1);
	close(0);
}
