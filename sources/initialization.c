#include "../libft/libft.h"
#include "../includes/command.h"

void	init_cursor(t_cursor *csr)
{
	(*csr).a = 0;
	(*csr).b = 0;
}

void	init_parser(t_parser *psr)
{
	(*psr).sep = -1;
	(*psr).command = NULL;
}
