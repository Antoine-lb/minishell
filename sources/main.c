#include "../includes/minishell.h"

int		*print_promt(void)
{
	static int i;

	return (&i);
}

int		get_fd_in_and_out(t_command *content, int *fdin, int *fdout)
{
	t_list	*redirections;
	int		input_has_changed;

	input_has_changed = 0;
	redirections = content->redirections;
	while (redirections)
	{
		if (((t_redirection *)(redirections->content))->sep == 4)
			*fdout = open(((t_redirection *)(redirections->content))->args, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (((t_redirection *)(redirections->content))->sep == 5)
			*fdout = open(((t_redirection *)(redirections->content))->args, O_RDWR | O_CREAT | O_APPEND, 0666);
		if (((t_redirection *)(redirections->content))->sep == 3)
			*fdin = open(((t_redirection *)(redirections->content))->args, O_RDONLY, 0666);
		redirections = redirections->next;
	}
	return (input_has_changed);
}

int		execute_commands(t_list *cmd_line)
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
		int infile = 0;
		int outfile = 0;
		content = (t_command *)(cmd_line->content);
		tab = execution(content);
		dup2(fdin, 0);
		close(fdin);
		ret = get_fd_in_and_out(content, &infile, &outfile);
		if (ret == -1)
			printf("error reading fdin or fdout\n");
		if (infile)
			fdin = infile;
		if (cmd_line->next == NULL)
		{
			if (outfile)
				fdout = outfile;
			else
				fdout = dup(tmpout);
		}
		else
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		*print_promt() = 1;
		ret = fork();
		if (ret == 0)
		{
			execve(ft_strjoin("/bin/", tab[0]), tab, NULL);
			perror("execve");
			exit(0);
		}
		else
			signal(SIGCHLD, SIG_IGN);
		cmd_line = cmd_line->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	wait(&status);
	return (0);
}

int		rep(void)
{
	int			ret;
	int			cnt;
	char		*line;
	t_command	*cmd_tmp;
	t_parser	*cmd_text;
	t_list		*cmds;
	t_list		*cmd;

	cmd = NULL;
	cmds = NULL;
	cnt = 1;
	ft_putstr_fd("# ", 1);
	*print_promt() = 0;
	ret = get_next_line(0, &line);
	while (command(&cmd_text, &line, cnt) > -1)
	{
		parse(cmd_text->sep, ft_strdup(cmd_text->command), &cmds, &cmd);
		cnt++;
	}
	parse(cmd_text->sep, ft_strdup(cmd_text->command), &cmds, &cmd);
	while (cmds)
	{
		execute_commands(((t_list *)(cmds->content)));
		cmds = cmds->next;
	}
	return (ret);
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (*print_promt() == 0)
			ft_putstr_fd("\n@", 1);
		else
			ft_putstr_fd("\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (*print_promt() == 1)
			ft_putstr_fd("Quit (core dumped)\n", 1);
	}
}

int		minshell(void)
{
	*print_promt() = 0;

	while (rep() > 0);
	return (0);
}

int		main(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	minshell();
}
