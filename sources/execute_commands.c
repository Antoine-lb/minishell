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
	*tab = NULL;
}

int		if_last_command(t_list *cmd_line, int *outfile, int *fdout, int *tmpout)
{
	if (cmd_line->next == NULL)
	{
		if (*outfile)
			*fdout = *outfile;
		else
			*fdout = dup(*tmpout);
	}
	return (0);
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
		if_last_command(cmd_line, &outfile, &fdout, &tmpout);
		if (cmd_line->next != NULL)
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
		if (ft_strlen(tab[0]) != 0) {
			exec_child(tab, env);
		}
		ft_cleartab(&tab);
		cmd_line = cmd_line->next;
	}
	wait(&status);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	return (1);
}
