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

int     ft_ngetnnext(char *str, int from, char *c)
{
	int	a;

	while (str[from])
        {
                a = 0;
		while (c[a] && str[from] != c[a])
			a++;
		if ((int)ft_strlen(c) == a)
		      return (from);
                from++;
        }
        return (from);
}
