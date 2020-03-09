#include "../includes/command.h"

void	parse_cmd(t_command *cmd, char *line)
{
	char		*tmp;

	tmp = ft_strtrim(line, " ");
	(*cmd).cmd = ft_substr(tmp, 0, ft_getnext(tmp, 0, ' '));
	free(tmp);
}

void	parse_args(t_command *cmd, char *arg)
{
	int				c;
	char			*tmp;
	t_cursor		csr;

	init_cursor(&tmp, &csr, &c);
	while (arg[csr.b++])
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
	}
	ft_pushstr(cmd, &tmp);
}

void	parse_arg(t_command *cmd, char *line)
{
	char	*tmp;
	char	*arg;
	char	*arg2;

	tmp = ft_strtrim(line, " ");
	arg2 = ft_strchr(tmp, ' ');
	if (arg2 != NULL)
	{
		arg2 = arg2 + 1;
		parse_args(cmd, arg2);
	}
}

void	parse_out(t_command *last, t_command *cmd)
{
	int				a;
	int				s;
	t_redirection	*red;

	a = 1;
	s = ft_lstsize(cmd->args) + 1;
	red = (t_redirection *)malloc(sizeof(t_redirection));
	red->sep = last->sep;
	red->args = ft_strdup(cmd->cmd);
	while (a < s)
	{
		ft_lstadd_back(&(last)->args, ft_lstnew((char *)(cmd->args->content)));
		cmd->args = cmd->args->next;
		a++;
	}
	last->sep = cmd->sep;
	ft_lstadd_back(&(last)->redirections, ft_lstnew(red));
}

void	parse(int sep, char *line, t_list **cmds, t_list **cmd)
{
	t_command		*cmd_tmp;
	t_list			*last;
	t_redirection	*red;

	cmd_tmp = (t_command *)malloc(sizeof(t_command));
	cmd_tmp->args = NULL;
	parse_cmd(cmd_tmp, line);
	cmd_tmp->sep = sep;
	parse_arg(cmd_tmp, line);
	last = ft_lstlast(*cmd);
	if (ft_lstsize(*cmd) > 0 &&
		((t_command *)(last->content))->sep > 2 &&
		((t_command *)(last->content))->sep < 6)
		parse_out(((t_command *)(last->content)), cmd_tmp);
	else
	{
		cmd_tmp->redirections = NULL;
		ft_lstadd_back(cmd, ft_lstnew(cmd_tmp));
	}
	if (sep == 1 || sep == -1)
	{
		ft_lstadd_back(cmds, ft_lstnew(*cmd));
		*cmd = NULL;
	}
	free(line);
}
