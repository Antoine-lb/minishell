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
	int nb;

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
		free_2d_array(*env);
		if (args[1] == NULL || args[2] != NULL)
		{		
			if (args[1] != NULL)
			{
				if (ft_isnumber(args[1]) != 0)
					last_exit_code(1);
				else
					last_exit_code(2);
			}
			exit(last_exit_code(-1));
		}	
		if ((nb = ft_isnumber(args[1])) != 0) {
			long long int arg = ft_atoi(args[1]);
			if (nb == 1) {
				if (arg >= 0 && arg <= 9223372036854775807)
					exit(arg % 256);
			} else {
				if (arg < 0 && arg > -9223372036854775807)
					exit(arg % 255);
				if (arg - 1 == 9223372036854775807)
					exit(0);
			}
		}
		exit(2);
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