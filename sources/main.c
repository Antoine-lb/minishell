#include "../includes/minishell.h"

char	**execution(t_command *cmd)
{
	int		a;
	char	**tab;

	a = ft_lstsize(cmd->args) + 1;
	tab = (char **)malloc(sizeof(char*) * (a + 1));
	tab[0] = cmd->cmd;
	a = 1;
	while (cmd->args)
	{
		tab[a] = (char *)cmd->args->content;
		cmd->args = cmd->args->next;
		a++;
	}
	tab[a] = NULL;
	return (tab);
}

int		execute_command(t_list *cmd_line)
{
	int			status;
	char		**tab;
	pid_t		pid_fils;
	t_command	*content;

	if (!cmd_line)
		cmd_line = NULL;
	while (cmd_line)
	{
		pid_fils = fork();
		if (pid_fils == 0)
		{
			content = cmd_line->content;
			tab = execution(content);
			execve(ft_strjoin("/bin/", tab[0]), tab, NULL);
			exit(0);
		}
		wait(&status);
		cmd_line = cmd_line->next;
	}
	return (0);
}

int		rep(void)
{
	int			ret;
	int			cnt;
	char		*line;
	t_command	*cmd_tmp;
	t_parser	*cmd_text;
	t_list		*cmd;

	cmd = NULL;
	cnt = 1;
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	while (command(&cmd_text, &line, cnt) > -1)
	{
		cmd_tmp = (t_command *)malloc(sizeof(t_command));
		parse(cmd_text->sep, ft_strdup(cmd_text->command), cmd_tmp);
		ft_lstadd_back(&cmd, ft_lstnew(cmd_tmp));
		cnt++;
	}
	cmd_tmp = (t_command *)malloc(sizeof(t_command));
	parse(cmd_text->sep, ft_strdup(cmd_text->command), cmd_tmp);
	ft_lstadd_back(&cmd, ft_lstnew(cmd_tmp));
	execute_command(cmd);
	return (ret);
}

int		main(void)
{
	while (rep() > 0);
	return (0);
}
