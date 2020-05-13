#include "libft.h"

void	ft_cjoin(char **s1, char *s2, int a)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = *s1;
	tmp2 = ft_substr(s2, a, 1);
	*s1 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
}

char	*ft_stripslashes(char *s1, char *s2)
{
	char	*cons;
	int		a;

	a = 0;
	cons = ft_strnew();
	while (s1[a + 1])
	{
		if (ft_includes(s1[a + 1], s2) && ((int)(s1[a])) == 92)
		{
			ft_cjoin(&cons, s1, a + 1);
			a++;
		}
		else
			ft_cjoin(&cons, s1, a);
		a++;
	}
	ft_cjoin(&cons, s1, a);
	return (cons);
}