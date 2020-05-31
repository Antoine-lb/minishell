/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:24:30 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 08:57:31 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_list(t_list *cmd)
{
	t_list	*lst;
	t_list	*tmp;

	lst = ((t_command *)((cmd)->content))->redirections;
	free(((t_command *)((cmd)->content))->cmd);
	free(((t_command *)((cmd)->content))->args);
	while (lst)
	{
		free((((t_redirection *)(lst)->content))->args);
		free((lst)->content);
		tmp = lst;
		lst = tmp->next;
		free(tmp);
	}
	free(lst);
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
	ft_putstr_fd("$> ", 0);
	*print_promt() = 0;
	ret = get_next_line(0, &line);
	cmd_text = (t_parser *)malloc(sizeof(t_parser));
	if (checker(&line, &cmd_text, env))
		return (ret);
	while (command(&cmd_text, &line, env))
	{
		parse(cmd_text, &cmds, &cmd);
		if (cmd_text->sep == 1)
			execute(&cmds, env);
	}
	parse(cmd_text, &cmds, &cmd);
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

int		main(int ac, char **av, char **environ)
{
	char	**env;

	(void)ac;
	(void)av;
	env = dup_env(environ);
	if (!env)
		printf("cannot allocate to dup environ\n");
	sort(env);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	minshell(&env);
	free_2d_array(env);
	return (last_exit_code(-1));
}
