#include "../includes/command.h"
#include <libc.h>

void			parse_cmd(t_command *cmd, t_parser psr)
{
	char		*tmp;

	tmp = ft_strtrim(psr.command, " ");
	if (ft_strcmp(tmp, "echo") == 0)
		(*cmd).cmd = 1;
	else if (ft_strcmp(tmp, "cd") == 0)
		(*cmd).cmd = 2;
	else if (ft_strcmp(tmp, "pwd") == 0)
		(*cmd).cmd = 3;
	else if (ft_strcmp(tmp, "export") == 0)
		(*cmd).cmd = 4;
	else if (ft_strcmp(tmp, "unset") == 0)
		(*cmd).cmd = 5;
	else if (ft_strcmp(tmp, "env") == 0)
		(*cmd).cmd = 6;
	else if (ft_strcmp(tmp, "exit") == 0)
		(*cmd).cmd = 7;
	else
		(*cmd).cmd = -1;
	free(tmp);
}

void			parse_flg(t_command *cmd, t_parser psr)
{
	int			a;
	char		*tmp;

	a = 0;
	(*cmd).flag = 0;
	tmp = ft_strtrim(psr.command, " ");
	while (tmp[a])
	{
		if (tmp[a] == 34 || tmp[a] == 39 || tmp[a] == 45)
		{
			if (tmp[a] == 45)
				(*cmd).flag = 1;
			return ;
		}
		a++;
	}
}

void			parse_args(t_command *cmd, char *arg)
{
	int			a;
	char		*t;
	t_list		*tt;
	t_cursor	csr;

	a = 0;
	init_cursor(&csr);
	while (arg[csr.b])
	{
		instring(&a, arg[csr.b]);
		if (a == 0)
		{
			if (arg[csr.b] == ' ')
			{
				t = ft_substr(arg, csr.a, csr.b - csr.a);
				tt = ft_lstnew((void *)ft_strtrim(t, " "));
				ft_lstadd_back(&(cmd->args), tt);
				csr.a = csr.b;
			}
		}
		csr.b++;
	}
	ft_substr(arg, csr.a, csr.b - csr.a);
}

void			parse_arg(t_command *cmd, t_parser psr)
{
	char		*tmp;
	char		*arg;
	char		*arg2;

	tmp = ft_strtrim(psr.command, " ");
	arg = ft_strrchr(tmp, '-');
	if (arg == NULL)
		arg2 = ft_strchr(tmp, ' ');
	else
		arg2 = ft_strchr(arg, ' ');
	if (arg2 != NULL)
		arg2 = arg2 + 1;
	parse_args(cmd, arg2);
}

t_command		parse(t_parser psr)
{
	t_command	cmd;
	cmd.args = NULL;

	parse_cmd(&cmd, psr);
	parse_flg(&cmd, psr);
	cmd.sep = psr.sep;
	parse_arg(&cmd, psr);
	return (cmd);
}