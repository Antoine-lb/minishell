#include "../includes/minishell.h"

void	d_command(t_command *cmd)
{
	int				a;
	t_redirection	*red;

	printf("command: %s\n", cmd->cmd);
	while (cmd->args)
	{
		printf("argument: %s\n", (char *)(cmd->args->content));
		cmd->args = cmd->args->next;
	}
	if (cmd->redirection)
	{
		while (cmd->redirection)
		{
			a = 0;
			red = ((t_redirection *)(cmd->redirection->content));
			printf("output: %d - [", red->sep);
			while (red->args[a + 1] != NULL)
			{
				printf("%s, ", red->args[a]);
				a++;
			}
			printf("%s]\n", red->args[a]);
			cmd->redirection = cmd->redirection->next;
		}
	}
	printf("\n===\n\n");
}

void	d_lcommand(t_list *cmds)
{
	while (cmds)
	{
		printf("___ new command ___\n");
		printf("\n===\n\n");
		while (cmds->content)
		{
			d_command((t_command *)(((t_list *)(cmds->content))->content));
			cmds->content = ((t_list *)(cmds->content))->next;
		}
		cmds = cmds->next;
	}
}

char	**execution(t_command *cmd)
{
	int				a;
	char			**tab;
	t_redirection	*red;

	a = ft_lstsize(cmd->args) + 1;
	tab = (char **)malloc(sizeof(char *) * (a + 1));
	tab[0] = cmd->cmd;
	a = 1;
	while (cmd->args)
	{
		tab[a] = (char *)cmd->args->content;
		cmd->args = cmd->args->next;
		a++;
	}
	tab[a] = NULL;
	if (cmd->redirection)
	{
		while (cmd->redirection)
		{
			a = 0;
			red = ((t_redirection *)(cmd->redirection->content));
			while (red->args[a + 1] != NULL)
				a++;
			cmd->redirection = cmd->redirection->next;
		}
	}
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

	int tmpin = dup(0);
	int tmpout = dup(1);

	int fdin = dup(tmpin);
	int fdout = dup(tmpout);

	int ret;
	while (cmd_line)
	{
		dup2(fdin, 0);
		close(fdin);

		if (cmd_line->next == NULL)
			fdout = dup(tmpout);
		else
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}

		dup2(fdout, 1);
		close(fdout);

		ret = fork();
		if (ret == 0)
		{
			content = cmd_line->content;
			tab = execution(content);
			execve(ft_strjoin("/bin/", tab[0]), tab, NULL);
			execve(tab[0], tab, NULL);
			perror("execve");
			exit(0);
		}
		else
			wait(&status);

		content = cmd_line->content;
		tab = execution(content);
		cmd_line = cmd_line->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
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
	t_list		*cmds;

	cmd = NULL;
	cmds = NULL;
	cnt = 1;
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	while (command(&cmd_text, &line, cnt) > -1)
	{
		parse(cmd_text->sep, ft_strdup(cmd_text->command), &cmds, &cmd);
		cnt++;
	}
	parse(cmd_text->sep, ft_strdup(cmd_text->command), &cmds, &cmd);
	d_lcommand(cmds);
	//execute_command(cmd);
	return (ret);
}

int		main(void)
{
	while (rep() > 0);
	return (0);
}
