#include "../includes/minishell.h"

extern char **environ;

void	clean_list(t_list *cmd)
{
	free(((t_command *)((cmd)->content))->cmd);
	free(((t_command *)((cmd)->content))->args);
	if (ft_lstsize(((t_command *)((cmd)->content))->redirections) > 0)
	{
		free((((t_redirection *)((((t_command *)
		((cmd)->content)))->redirections)->content))->args);
		free(((((t_command *)((cmd)->content)))->redirections)->content);
	}
	free(((t_command *)((cmd)->content))->redirections);
}

void	execute(t_list **cmds, char ***env)
{
	t_list	*cmd;
	t_list	*cm;

	cmd = NULL;
	cm = NULL;
	while ((*cmds))
	{
		execute_commands(((t_list *)((*cmds)->content)), env);
		cmd = (t_list *)((*cmds)->content);
		while (cmd)
		{
			clean_list(cmd);
			cm = cmd->next;
			free((cmd)->content);
			free(cmd);
			cmd = cm;
		}
		cmd = (*cmds)->next;
		free((*cmds));
		(*cmds) = cmd;
	}
}

int		rep(char ***env)
{
	int			ret;
	char		*line;
	t_parser	*cmd_text;
	t_list		*cmds;
	t_list		*cmd;

	cmd = NULL;
	cmds = NULL;
	ft_putstr_fd("# ", 0);
	*print_promt() = 0;
	ret = get_next_line(0, &line);
	while (command(&cmd_text, &line, env))
	{
		parse(cmd_text->sep, ft_strdup(cmd_text->command), &cmds, &cmd, env);
		free(cmd_text->command);
		if (cmd_text->sep == 1)
			execute(&cmds, env);
	}
	parse(cmd_text->sep, ft_strdup(cmd_text->command), &cmds, &cmd, env);
	free(cmd_text->command);
	free(cmd_text);
	free(line);
	execute(&cmds, env);
	return (ret);
}

int		minshell(char ***env)
{
	*print_promt() = 0;
	while (rep(env) > 0)
	{
	}
	return (0);
}

int		main(void)
{
	char	**env;

	env = dup_env(environ);
	if (!env)
		printf("cannot allocate to dup environ\n");
	sort(env);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	minshell(&env);
	free_2d_array(env);
	return (0);
}
