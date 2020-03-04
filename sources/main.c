#include "../includes/minishell.h"

char **execution(t_command *cmd)
{
	int a;
	char **tab;

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
	a = 0;
	while (tab[a])
	{
		printf("tab[%d] = %s\n", a, tab[a]);
		a++;
	}
	printf("==\n");
	return (tab);
}

// /bin/cat ./remnum.c | /usr/bin/grep if
int execute_command(t_list *cmd_line)
{
	int			status;
	char		**tab;
	pid_t		pid_fils;
	t_command	*content;

	if (!cmd_line)
		cmd_line = NULL;

	int tmpin = dup(0);
	int tmpout = dup(1);

	int fdin = dup(tmpin); // if is a file would be different
	int fdout = dup(tmpout);

	int ret;
	while (cmd_line)
	{
		// dup2(fdin, 0);
		// close(fdin);

		// if (cmd_line->next == NULL)
		// {
		// 	// if has to output to a file change stdout
		// 	fdout = dup(tmpout);
		// }
		// else
		// {
		// 	// no last command so it has to be a pipe
		// 	int fdpipe[2];
		// 	pipe(fdpipe);
		// 	fdout = fdpipe[1];
		// 	fdin = fdpipe[0];
		// }

		// // redirect the output
		// dup2(fdout, 1);
		// close(fdout);

		// ret = fork();
		// if (ret == 0)
		// {
		// 	content = cmd_line->content;
		// 	tab = execution(content);
		// 	// execve(ft_strjoin("/bin/", tab[0]), tab, NULL);
		// 	execve(tab[0], tab, NULL);
		// 	perror("execve");
		// 	exit(0);
		// }
		// else
		// {
		// 	wait(&status);
		// }

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
	while (rep() > 0)
		;
	return (0);
}
