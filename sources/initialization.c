#include "../libft/libft.h"
#include "../includes/command.h"

void	init_cursor(char **tmp, t_cursor *csr)
{
	(*csr).a = -1;
	(*csr).b = -1;
	(*csr).c = 0;
	(*tmp) = NULL;
}

void	init_parser(t_parser *psr)
{
	(*psr).sep = -1;
	(*psr).command = NULL;
}
