#include "libft.h"

int	ft_getnext(char *str, int from, char c)
{
	while (str[from])
	{
		if (str[from] == c)
			return (from);
		from++;
	}
	return (from);
}

int     ft_ngetnext(char *str, int from, char *c)
{
	int	a;
	int	b;
	int	t;

	a = 0;
        b = 0;
	t = 0;
	while (c[a])
	{
		t = ft_getnext(str, from, c[a]);
		if (a == 0 || t < b)
			b = t;
		a++;
	}
        return (b);
}
