#include "../libft/libft.h"
#include "../includes/command.h"

int		last_exit_code(int val)
{
	static int	last_val;

	if (val >= 0)
		last_val = val;
	return (last_val);
}

void	initparser(t_parser **psr)
{
	*psr = (t_parser *)malloc(sizeof(t_parser));
	(*psr)->command = ft_strdup("");
}

int		ft_string(char *str, int b)
{
	static int		a;
	static int		c;

	if (c != 0)
	{
		a = (int)(str[b - 1]);
		c = 0;
	}
	if ((int)(str[b]) == 39 || (int)(str[b]) == 34)
	{
		if (a == 0 && ((int)(str[b - 1]) != 92 || b == 0))
			c = (int)(str[b]);
		else if (((int)(str[b]) == 39 ||
					(int)(str[b]) == 34) && ((int)str[b - 1]) != 92)
			a = 0;
	}
	if (a != 0)
		return (a);
	return (0);
}

void	bcommand(t_parser **psr, char **line, char ***env, int *a)
{
	if ((*line)[*a] != 92 || ((*line)[*a] == 92
	&& ft_includes((*line)[*a + 1], " \t"))
	|| ft_includes((*line)[(*a) + 1], "$\'\""))
	{
		ft_parser(psr, env, (*line)[*a], 0);
		if ((*line)[*a] == 92)
		{
			*a = ft_ngetnnext((*line), (*a) + 1, " \t") - 1;
			if (ft_includes((*line)[(*a) + 1], "$\'\""))
				(*a)++;
			ft_parser(psr, env, (*line)[*a], 0);
		}
	}
}

int		command(t_parser **psr, char **line, char ***env)
{
	int				a;
	static int		b;
	int				d;
	char			*tmp;

	a = b;
	d = 0;
	initparser(psr);
	while ((*line)[a] != '\0' && (*line)[a + 1] != '\0')
	{
		if ((d = ft_string(*line, a)) == 0)
		{
			if (rcommand(psr, line, a, &b))
				return (1);
			bcommand(psr, line, env, &a);
		}
		else
			ft_parser(psr, env, (*line)[a], d);
		a++;
	}
	ft_parser(psr, env, (*line)[a], d);
	if ((*line)[a] != '\0')
		ft_parser(psr, env, (*line)[a + 1], d);
	ft_retnormal(psr, &b);
	return (0);
}
