#include "../libft/libft.h"
#include "../includes/command.h"

void	ecommand1(t_parser **psr, char **line, int a)
{
	char	*tmp;

	tmp = ft_strtrim((*psr)->command, " \t");
	if ((ft_strlen(tmp) == 0 &&
	ft_includes((*line)[ft_ngetnnext((*line), a + 1, " \t")], ";|<>")))
	{
		ft_putstr_fd("minishell: syntax error\n", 0);
		exit(2);
	}
	free(tmp);
}

void	ecommand2(char **line, int c)
{
	char	*tmp;

	tmp = ft_strtrim((*line), " \t");
	if (((ft_includes(tmp[0], ";|")) && c < 3))
	{
		ft_putstr_fd("minishell: syntax error\n", 0);
		exit(2);
	}
	free(tmp);
}

int		rcommand(t_parser **psr, char **line, int a, int *b)
{
	int		c;

	if ((c = ft_getnext(";|<>", 0, (*line)[a])) < 4 && (*line)[a - 1] != 92)
	{
		ecommand1(psr, line, a);
		ecommand2(line, c);
		if (c == 3 && (*line)[a + 1] == '>')
			c = 4;
		(*psr)->sep = c;
		if (c == 4)
			a++;
		*b = a + 1;
		(*psr)->sep++;
		return (1);
	}
	return (0);
}
