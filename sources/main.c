#include "../includes/minishell.h"

void	fdf(void *cmd)
{
	printf("cmd->cmd = %s\n", ((t_command*)cmd)->cmd);
}

int execute_command(t_list *cmd_line)
{
	int status;
	pid_t pid_fils;
	t_command *content;

	if (!cmd_line)
		cmd_line = NULL;
	pid_fils = fork();
	while (cmd_line)
	{
		if (pid_fils == 0)
		{
			content = cmd_line->content;
			printf("content->cmd = %s\n", content->cmd);
			execl ("/bin/ls", NULL) ;

			exit(0);
		}
		else {
			wait(&status);
			pid_fils = fork();
		}
		cmd_line = cmd_line->next;
	}
	wait(&status);

	return (0);
}

int rep(void)
{
	int ret;
	int cnt;
	char *line;
	t_command *cmd_tmp;
	t_parser cmd_text;
	t_list *cmd;

	cmd = NULL;
	cnt = 1;
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	while ((cmd_text = command(&line, cnt)).sep > -1)
	{
		cmd_tmp = (t_command *)malloc(sizeof(t_command));
		parse(cmd_text, cmd_tmp);
		ft_lstadd_back(&cmd, ft_lstnew(cmd_tmp));
		cnt++;
	}
	cmd_tmp = (t_command *)malloc(sizeof(t_command));
	parse(cmd_text, cmd_tmp);
	ft_lstadd_back(&cmd, ft_lstnew(cmd_tmp));
	ft_lstiter(cmd, fdf);
	execute_command(cmd);
	return (ret);
}

int main(void)
{
	while (rep() > 0);
	return (0);
}
