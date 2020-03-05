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

void			parse(int sep, char *line, t_list **cmds, t_list **cmd)
{
	t_command		*cmd_tmp;
	t_list			*last;
	t_redirection	*red;
	int				s;
	int				a;
	int				b;
	int				prev_sep;

	s = ft_lstsize(*cmd);
	prev_sep = ((t_command *)(last->content))->sep;
	cmd_tmp = (t_command *)malloc(sizeof(t_command));
	cmd_tmp->args = NULL;
	parse_cmd(cmd_tmp, line);
	cmd_tmp->sep = sep;
	parse_arg(cmd_tmp, line);
	if (s > 0)
	{
		last = ft_lstlast(*cmd);
		if (((t_command *)(last->content))->sep > 2 && ((t_command *)(last->content))->sep < 6)
		{
			a = 1;
			b = ft_lstsize(cmd_tmp->args) + 1;
			red = (t_redirection *)malloc(sizeof(t_redirection));
			red->sep = ((t_command *)(last->content))->sep;
			red->args = (char **)malloc(sizeof(char *) * (b + 1));
			red->args[0] = cmd_tmp->cmd;
			while (a < b)
			{
				red->args[a] = (char *)(cmd_tmp->args->content);
				cmd_tmp->args = cmd_tmp->args->next;
				a++;
			}
			red->args[a] = NULL;
			((t_command *)(last->content))->sep = cmd_tmp->sep;
			ft_lstadd_back(&(((t_command *)(last->content))->redirection), ft_lstnew(red));
		}
		else
		{
			cmd_tmp->redirection = NULL;
			ft_lstadd_back(cmd, ft_lstnew(cmd_tmp));
		}
	}
	else
	{
		cmd_tmp->redirection = NULL;
		ft_lstadd_back(cmd, ft_lstnew(cmd_tmp));
	}
	if (sep == 1 || sep == -1)
	{
		ft_lstadd_back(cmds, ft_lstnew(*cmd));
		*cmd = NULL;
	}
	free(line);
}
