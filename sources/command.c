#include "../libft/libft.h"
#include "../includes/command.h"

void		instring(int *a, char c)
{
	if (c == 39 || c == 34)
	{
		if ((*a) == 0)
			(*a) = 1;
		else
			(*a) = 0;
	}
}

char		*display(char *line, int *a, int *b)
{
	char	*tmp;
	char	*str;

	if (line[(*a)] == '>' && line[(*b)] != '>')
		tmp = ft_substr(line, (*a), (*b) - (*a));
	else if (line[(*a)] != '>' && line[(*b)] == '>')
		tmp = ft_substr(line, (*a), (*b) - (*a) - 2);
	else if (line[(*a)] == '>' && line[(*b)] == '>')
		tmp = ft_substr(line, (*a), (*b) - (*a) + 1);
	else
		tmp = ft_substr(line, (*a), (*b) - (*a) - 1);
	str = ft_strtrim(tmp, " ");
	(*a) = (*b);
	(*a)++;
	free(tmp);
	return (str);
}

int			get_separator(char c1, char c2)
{
	int		cmd;

	cmd = 0;
	if (c1 == ';')
		cmd = 1;
	else if (c1 == '|')
		cmd = 2;
	else if (c1 == '<')
		cmd = 3;
	else if (c1 == '>')
	{
		cmd = 4;
		if (c2 == '>')
			cmd = 5;
	}
	return (cmd);
}

t_parser	get_command(char *line, t_cursor *csr, int *d)
{
	t_parser	ret;

	ret.sep = get_separator(line[(*csr).b], line[(*csr).b + 1]);
	if (ret.sep > 0 && ret.sep < 6)
	{
		if (ret.sep == 5)
			(*csr).b++;
		if (line[(*csr).a] == '>' && line[(*csr).a + 1] == '>')
			(*csr).a++;
		ret.command = display(line, &(csr->a), &(csr->b));
		(*d)++;
	}
	return (ret);
}

t_parser	command(char **line, int nb)
{
	t_cursor	csr;
	t_parser	psr;
	int			c;
	int			d;

	init_cursor(&csr);
	init_parser(&psr);
	c = 0;
	d = 0;
	while ((*line)[csr.b] && d < nb)
	{
		instring(&c, (*line)[csr.b]);
		if (c == 0)
		{
			psr = get_command(*line, &csr, &d);
			if (get_separator((*line)[csr.b], (*line)[csr.b + 1]) > 0)
				free(psr.command);
		}
		csr.b++;
	}
	if (d < nb)
	{
		psr.sep = -1;
		csr.b = ft_strlen(*line);
		psr.command = ft_substr(*line, csr.a, csr.b);
	}
	return (psr);
}
