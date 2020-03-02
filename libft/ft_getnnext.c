#include "libft.h"

int		ft_getnnext(char *str, int from, char c)
{
	while (str[from])
	{
		if (str[from] != c)
			return (from);
		from++;
	}
	return (from);
}
