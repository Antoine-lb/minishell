/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 09:13:35 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/30 12:13:17 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void exec_child(char **args, char ***env)
{
	char *tmp;
	int ret;

	if (ft_strcmp(args[0], "env") == 0)
	{
		bi_env(*env);
	}
	else if (ft_strcmp(args[0], "export") == 0)
	{
		bi_export(args, env);
	}
	else if (ft_strcmp(args[0], "unset") == 0)
	{
		bi_unset(args, env);
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		bi_pwd(env);
		last_exit_code(0);
	}
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		bi_exit(args, env);
	}
	else if (ft_strcmp(args[0], "echo") == 0) {
		bi_echo(args);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		bi_cd(args, env);
	}
	else
	{
		ret = fork();
		if (ret == 0)
		{
 			tmp = get_path_from_env(args[0], env);
			if (tmp != NULL)
			{
				execve(tmp, args, *env);
				perror("execve");
			}
			else
			{
				ft_putstr_fd("minishell: [", 2);
				ft_putstr_fd(args[0], 2);
				ft_putstr_fd("] command not found\n", 2);
				last_exit_code(127);
			}
			free(tmp);
			exit(last_exit_code(-1));
		} else {
			int status;
		
			waitpid(ret, &status, 0);
			last_exit_code(status >> 8);
		}
	}
}