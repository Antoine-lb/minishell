#include "../includes/command.h"

void	parse_cmd(t_command *cmd, char *line)
{
	char		*tmp;

	tmp = ft_strtrim(line, " ");
	(*cmd).cmd = ft_substr(tmp, 0, ft_getnext(tmp, 0, ' '));
	free(tmp);
}

void	parse_args(t_command *cmd, char *arg, char ***local_env)
{
	char			*tmp;
	t_cursor		csr;

	init_cursor(&tmp, &csr);
	while (arg[csr.b++])
	{
		if (csr.a == -1)
		{
			if (csr.c == 0)
				csr.b = ft_getnnext(arg, csr.b, ' ');
			if ((int)(arg[csr.b]) == 39 || (int)(arg[csr.b]) == 34)
				ft_openaall(&csr, cmd, &tmp, arg);
			else
				ft_opennorm(&csr, cmd, &tmp, arg, local_env);
		}
		else
		{
			if ((int)(arg[csr.b]) == 39 && (int)(arg[csr.a - 1]) == 39)
				ft_closea39(&csr, cmd, &tmp, arg);
			else if ((int)(arg[csr.b]) == 34 && (int)(arg[csr.a - 1]) == 34)
				ft_closea34(&csr, cmd, &tmp, arg, local_env);
		}
	}
	ft_pushstr(cmd, &tmp);
}

void	parse_arg(t_command *cmd, char *line, char ***local_env)
{
	char	*tmp;
	char	*tmp2;
	char	*arg;

	tmp = ft_strtrim(line, " ");
	if (tmp != NULL)
	{
		arg = ft_strchr(tmp, ' ');
		if (arg != NULL)
		{
			tmp2 = arg + 1;
			parse_args(cmd, tmp2, local_env);
		}
		free(tmp);
	}
	/*if (tmp != NULL)
	{
		arg = ft_strchr(tmp, ' ') + 1;
		parse_args(cmd, arg, local_env);
	}*/
}

void	parse_out(t_command *last, t_command *cmd)
{
	int				a;
	int				s;
	t_redirection	*red;
	t_list			*tmp;

	a = 1;
	s = ft_lstsize(cmd->args) + 1;
	red = (t_redirection *)malloc(sizeof(t_redirection));
	red->sep = last->sep;
	red->args = ft_strdup(cmd->cmd);
	while (a < s)
	{
		if (a == 1 && ft_strcmp(last->cmd, "") == 0)
			last->cmd = (char *)(cmd->args->content);
		else
			ft_lstadd_back(&(last->args), ft_lstnew((char *)(cmd->args->content)));
		tmp = cmd->args->next;
		free(cmd->args);
		cmd->args = tmp;
		a++;
	}
	last->sep = cmd->sep;
	ft_lstadd_back(&(last)->redirections, ft_lstnew(red));
}

void	parse(int sep, char *line, t_list **cmds, t_list **cmd, char ***local_env)
{
	t_command	*cmd_tmp;
	t_list		*last;
	t_list		*tmp;

	cmd_tmp = (t_command *)malloc(sizeof(t_command));
	cmd_tmp->args = NULL;
	parse_cmd(cmd_tmp, line);
	cmd_tmp->sep = sep;
	parse_arg(cmd_tmp, line, local_env);
	last = ft_lstlast(*cmd);
	if (ft_lstsize(*cmd) > 0 &&
		((t_command *)(last->content))->sep > 2 &&
		((t_command *)(last->content))->sep < 6) {
		parse_out(((t_command *)(last->content)), cmd_tmp);
		free(cmd_tmp->cmd);
		free(cmd_tmp);
	} else {
		cmd_tmp->redirections = NULL;
		tmp = ft_lstnew(cmd_tmp); 
		ft_lstadd_back(cmd, tmp);
	}
	if (sep == 1 || sep == -1)
	{
		tmp = ft_lstnew(*cmd);
		ft_lstadd_back(cmds, tmp);
		*cmd = NULL;
	}
    	free(line);
}
