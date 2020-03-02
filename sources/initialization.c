#include "../libft/libft.h"
#include "../includes/command.h"

void	init_cursor(char **tmp, t_cursor *csr, int *c)
{
	(*csr).a = -1;
	(*csr).b = 0;
	(*tmp) = NULL;
	(*c) = 0;
}

void	init_parser(t_parser *psr)
{
	(*psr).sep = -1;
	(*psr).command = NULL;
}
