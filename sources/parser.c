#include "../includes/command.h"

void			parse_cmd(t_command *cmd, char *line)
{
	char		*tmp;

	tmp = ft_strtrim(line, " ");
	(*cmd).cmd = ft_substr(tmp, 0, ft_getnext(tmp, 0, ' '));
	free(tmp);
}

void			parse_args(t_command *cmd, char *arg)
{
	int			c;
	char		*tmp;
	t_cursor	csr;

	init_cursor(&tmp, &csr, &c);
	while (arg[csr.b])
	{
		if (csr.a == -1)
		{
			csr.b = ft_getnnext(arg, csr.b, ' ');
			if ((int)(arg[csr.b]) == 39 || (int)(arg[csr.b]) == 34)
				ft_openaall(&csr, &c, cmd, &tmp, arg);
			else if (c == 0 || (int)(arg[csr.b]) == 92)
				ft_opennorm(&csr, &c, cmd, &tmp, arg);
		}
		else
		{
			if ((int)(arg[csr.b]) == 39 && (int)(arg[csr.a - 1]) == 39)
				ft_closea39(&csr, &c, cmd, &tmp, arg);
			else if ((int)(arg[csr.b]) == 34 && (int)(arg[csr.a - 1]) == 34)
				ft_closea34(&csr, &c, cmd, &tmp, arg);
		}
		csr.b++;
	}
	ft_pushstr(cmd, &tmp);
}

void			parse_arg(t_command *cmd, char *line)
{
	char		*tmp;
	char		*arg;
	char		*arg2;

	tmp = ft_strtrim(line, " ");
	arg2 = ft_strchr(tmp, ' ');
	if (arg2 != NULL)
	{
		arg2 = arg2 + 1;
		parse_args(cmd, arg2);
	}
}

void			parse(int sep, char *line, t_command *cmd)
{
	cmd->args = NULL;

	parse_cmd(cmd, line);
	cmd->sep = sep;
	parse_arg(cmd, line);
	free(line);
}
