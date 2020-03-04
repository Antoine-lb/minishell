#include "../includes/minishell.h"

int get_fd_in_and_out(t_command *content, int *fdin, int *fdout)
{
	t_list *redirections;

	redirections = content->redirections;
	while (redirections)
	{
		if (ft_strcmp(redirections->content, ">") == 0)
		{
			redirections = redirections->next;
			*fdout = open(redirections->content, O_RDWR | O_CREAT | O_TRUNC, 0666);
		}
		if (ft_strcmp(redirections->content, ">>") == 0)
		{
			redirections = redirections->next;
			*fdout = open(redirections->content, O_RDWR | O_CREAT | O_APPEND, 0666);
		}
		if (ft_strcmp(redirections->content, "<") == 0)
		{
			redirections = redirections->next;
			*fdin = open(redirections->content, O_RDONLY, 0666);
		}
		redirections = redirections->next;
	}

	return (0);
}

int execute_commands(t_list *cmd_line)
{
	int status;
	char **tab;
	pid_t pid_fils;
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
		content = filter_cmd(cmd_line->content);

		tab = execution(content);

		if (cmd_line->next == NULL)
		{
			// if has to output to a file change stdout
			fdout = dup(tmpout);
		}
		else
		{
			// no last command so it has to be a pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}

		ret = get_fd_in_and_out(content, &fdin, &fdout);
		if (ret == -1)
			printf("error reading fdin or fdout\n");

		dup2(fdin, 0);
		close(fdin);
		dup2(fdout, 1);
		close(fdout);

		ret = fork();
		if (ret == 0)
		{
			// execve(ft_strjoin("/bin/", tab[0]), tab, NULL);
			execve(tab[0], tab, NULL);
			perror("execve");
			exit(0);
		}
		else
		{
			// int status;
			// wait(&status);
			// printf("statuss = %d\n", status);
			while (wait(NULL) > 0)
				;
		}

		cmd_line = cmd_line->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	// int status;
	// wait(&status);
	// printf("statuss = %d\n", status);
	return (0);
}

int rep(void)
{
	int ret;
	int cnt;
	char *line;
	t_command *cmd_tmp;
	t_parser *cmd_text;
	t_list *cmd;

	cmd = NULL;
	cnt = 1;
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	while (command(&cmd_text, &line, cnt) > -1)
	{
		parse(cmd_text->sep, ft_strdup(cmd_text->command), &cmd);
		cnt++;
	}
	parse(cmd_text->sep, ft_strdup(cmd_text->command), &cmd);
	execute_commands(cmd);
	return (ret);
}

int main(void)
{
	while (rep() > 0)
		;
	return (0);
}
