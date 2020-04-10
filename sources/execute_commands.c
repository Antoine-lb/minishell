/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 09:13:35 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/30 12:13:17 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			}
		}
		else if (sep == 4)
		{
			*fdout = open(((t_redirection *)(redirections->content))->args, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (!is_last_symbol(redirections, 4) || !is_last_symbol(redirections, 5))
			{
				close(*fdout);
			}
		}
		else if (sep == 5)
		{
			*fdout = open(((t_redirection *)(redirections->content))->args, O_RDWR | O_CREAT | O_APPEND, 0666);
			if (!is_last_symbol(redirections, 4) || !is_last_symbol(redirections, 5))
			{
				close(*fdout);
			}
		}
		redirections = redirections->next;
	}
	return (input_has_changed);
}

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
		char *buf;
		buf = (char *)malloc(sizeof(char) * CWD_BUFFER_SIZE);
		getcwd(buf, CWD_BUFFER_SIZE);
		ft_putstr_fd(buf, 1);
		ft_putstr_fd("\n", 1);
		free(buf);
	}
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		// FREE EVERYTHING
		free_2d_array(*env);
		exit(0);
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
			tmp = get_path_from_env(args[0]);
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
			}
			free(tmp);
			exit(0);
		}
		else
			signal(SIGCHLD, SIG_IGN);
	}
}

void    ft_cleartab(char ***tab)
{
    int a;
    
    a = 0;
    while ((*tab)[a] != NULL)
    {
        free((*tab)[a]);
        (*tab)[a] = NULL;
        a++;
    }
    free(*tab);
    (*tab) = NULL;
}

int execute_commands(t_list *cmd_line, char ***env)
{
	int status;
	char **tab;
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
		ret = get_fd_in_and_out(content, &infile, &outfile);
		if (ret == -1)
			printf("error reading fdin or fdout\n");
		if (infile)
			fdin = infile;
		dup2(fdin, 0);
		close(fdin);
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
			exec_child(tab, env);
        ft_cleartab(&tab);
		cmd_line = cmd_line->next;
	}
	wait(&status);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	return (0);
}
