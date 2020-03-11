#include "../includes/minishell.h"

int *print_promt(void)
{
	static int i;

	return (&i);
}

int is_last_symbol(t_list *redirections, int target)
{
	int sep;

	redirections = redirections->next;
	while (redirections)
	{
		sep = (int)((t_redirection *)(redirections->content))->sep;

		if (sep == target)
		{
			return (0);
		}
		redirections = redirections->next;
	}
	return (1);
}

int get_fd_in_and_out(t_command *content, int *fdin, int *fdout)
{
	t_list *redirections;
	int input_has_changed;
	int sep;

	input_has_changed = 0;
	redirections = content->redirections;
	while (redirections)
	{
		sep = (int)((t_redirection *)(redirections->content))->sep;
		if (sep == 3)
		{
			*fdin = open(((t_redirection *)(redirections->content))->args, O_RDONLY, 0666);
			if (!is_last_symbol(redirections, 3))
			{
				close(*fdin);
				ft_putstr_fd("close <\n", 1);
			}
		}
		else if (sep == 4)
		{
			*fdout = open(((t_redirection *)(redirections->content))->args, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (!is_last_symbol(redirections, 4) || !is_last_symbol(redirections, 5))
			{
				close(*fdout);
				ft_putstr_fd("close >\n", 1);
			}
		}
		else if (sep == 5)
		{
			*fdout = open(((t_redirection *)(redirections->content))->args, O_RDWR | O_CREAT | O_APPEND, 0666);
			if (!is_last_symbol(redirections, 4) || !is_last_symbol(redirections, 5))
			{
				close(*fdout);
				ft_putstr_fd("close >>\n", 1);
			}
		}
		redirections = redirections->next;
	}
	return (input_has_changed);
}

int execute_commands(t_list *cmd_line)
{
	int status;
	char **tab;
	char *tmp;
	t_command *content;

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
			fdin = fdpipe[0];
			if (outfile)
			{
				fdout = outfile;
				close(fdpipe[1]);
			}
			else
				fdout = fdpipe[1];
		}
		dup2(fdout, 1);
		close(fdout);
		*print_promt() = 1;
		if (ft_strlen(tab[0]) != 0)
		{
			ret = fork();
			if (ret == 0)
			{
				tmp = get_path_from_env(tab[0]);
				execve(tmp, tab, NULL);
				perror("execve");
				free(tmp);
				exit(0);
			}
			else
				signal(SIGCHLD, SIG_IGN);
		}
		cmd_line = cmd_line->next;
	}
	wait(&status);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	return (0);
}

int		rep(void)
{
	int		ret;
	int		cnt;
	char	*line;
	t_command *cmd_tmp; // WHEN THIS UNUSED VARIABLE IS REMOVED it breaks the code (multiple new lines with no arguments)
	t_parser *cmd_text;
	t_list *cmds;
	t_list *cmd;

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

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (*print_promt() == 0)
			ft_putstr_fd("\n#", 1);
		else
			ft_putstr_fd("\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (*print_promt() == 1)
			ft_putstr_fd("Quit (core dumped)\n", 1);
	}
}

int minshell(void)
{
	*print_promt() = 0;

	while (rep() > 0);
	return (0);
}

int main(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	minshell();
}
