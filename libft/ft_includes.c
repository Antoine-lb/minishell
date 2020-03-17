#include "libft.h"

int		ft_includes(char c, char *str)
{
	int		a;

	a = 0;
	while (str[a])
	{
		if (c == str[a])
			return (1);
		a++;
	}
	return (0);
}