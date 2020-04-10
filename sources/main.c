#include "../includes/minishell.h"

extern char **environ;

int rep(char ***env)
{
	int		ret;
	int		cnt;
	char	*line;
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
	free(line);
	while (cmds)
	{
        cmd = cmds;
		execute_commands(((t_list *)(cmd->content)), env);
		cmds = cmd->next;
        free(((t_command *)(((t_list *)(cmd->content))->content))->cmd);
        ((t_command *)(((t_list *)(cmd->content))->content))->cmd = NULL;
        free(cmd->content);
        cmd->content = NULL;
        free(cmd);
        cmd = NULL;
	}
	return (ret);
}

int minshell(char ***env)
{
	*print_promt() = 0;

	while (rep(env) > 0);
	return (0);
}

int main(void)
{
	char	**env;

	env		= dup_env(environ);
	if (!env)
		printf("cannot allocate to dup environ\n");
	sort(env);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	minshell(&env);
}
