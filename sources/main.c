#include "../includes/minishell.h"

int rep(void)
{
	int ret;
	int cnt;
	char *line;
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

int minshell(void)
{
	*print_promt() = 0;

	while (rep() > 0)
		;
	return (0);
}

int main(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	minshell();
}
