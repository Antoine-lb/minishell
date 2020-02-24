#include "../libft/libft.h"
#include <libc.h>

void	print_tab(char **tab)
{
	int		a;

	a = 0;
	while (tab[a] != NULL)
	{
		ft_putstr_fd(ft_strtrim(tab[a], " "), 1);
		ft_putstr_fd("\n", 1);
		a++;
	}
}

void	command(char *line)
{
	int		a;
	int		b;
	int		c;

	a = 0;
	b = 0;
	c = 0;
	while (line[b])
	{
		if (line[b] == 39 || line[b] == 34)
		{
			if (c == 0)
				c = 1;
			else
				c = 0;
		}
		if (c == 0)
		{
			if (line[b] == ';' || line[b] == '|')
			{
				if (line[a] == ';' || line[a] == '|')
					a++;
				printf("%d - %d\n", a, b - 1);
				a = b;
			}
		}
		b++;
	}
	if (line[a] == ';' || line[a] == '|')
		a++;
	printf("%d - %d\n", a, b);
}
