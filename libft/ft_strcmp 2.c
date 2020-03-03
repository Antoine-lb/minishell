#include "libft.h"

int		ft_strcmp(char *s1, char *s2)
{
	unsigned int a;

	a = 0;
	while (s1[a] == s2[a] && s1[a] != '\0' && s2[a] != '\0')
		a++;
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}
