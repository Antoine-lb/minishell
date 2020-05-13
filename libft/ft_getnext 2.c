#include "libft.h"

int		ft_getnext(char *str, int from, char c)
{
	while (str[from])
	{
		if (str[from] == c)
			return (from);
		from++;
	}
	return (from);
}
