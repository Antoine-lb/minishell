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
			if (c == 0)
				csr.b = ft_getnnext(arg, csr.b, ' ');
			if ((int)(arg[csr.b]) == 39 || (int)(arg[csr.b]) == 34)
				ft_openaall(&csr, &c, cmd, &tmp, arg);
			else
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

void			parse(int sep, char *line, t_list **cmd)
{
	t_command	*cmd_tmp;
	int			s;
	int			c;

	c = 0;
	s = ft_lstsize(*cmd);
	cmd_tmp = (t_command *)malloc(sizeof(t_command));
	while (c < s - 1)
	{
		(*cmd) = (*cmd)->next;
		c++;
	}
	/*if (s > 0)
	{
		if (((t_command *)((*cmd)->content))->sep == 3)
	}*/
	cmd_tmp->args = NULL;
	parse_cmd(cmd_tmp, line);
	cmd_tmp->sep = sep;
	parse_arg(cmd_tmp, line);
	/*if (s > 0 && (t_command *)((*cmd->content))->sep == 3)
	{
		(t_command *)((*cmd->content))
	}
	else*/
	ft_lstadd_back(cmd, ft_lstnew(cmd_tmp));
	free(line);
}
