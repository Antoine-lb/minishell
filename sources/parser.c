#include "../includes/command.h"

void	parse(int sep, char *line, t_list **cmds,
t_list **cmd, char ***local_env)
{
	t_command	*cmd_tmp;
	t_list		*last;
	t_list		*tmp;

	cmd_tmp = parse_cmd(line, sep, local_env);
	last = ft_lstlast(*cmd);
	if (ft_lstsize(*cmd) > 0 &&
	((t_command *)(last->content))->sep > 2 &&
	((t_command *)(last->content))->sep < 6)
	{
		parse_out(((t_command *)(last->content)), cmd_tmp);
		free(cmd_tmp->cmd);
		free(cmd_tmp);
	}
	else
	{
		cmd_tmp->redirections = NULL;
		tmp = ft_lstnew(cmd_tmp);
		ft_lstadd_back(cmd, tmp);
	}
	if (sep == 1 || sep == -1)
		parse_last(tmp, cmd, cmds);
	free(line);
}
