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

void	ft_cleartab(char ***tab)
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

void	wire_outfile(int *fdin, int *fdout, int *outfile)
{
	int fdpipe[2];

	pipe(fdpipe);
	*fdin = fdpipe[0];
	if (*outfile)
	{
		*fdout = *outfile;
		close(fdpipe[1]);
	}
	else
		*fdout = fdpipe[1];
}

void	execute_command(t_list *cmd_line, char ***env, t_execute_commands *g)
{
	int infile;
	int outfile;

	infile = 0;
	outfile = 0;
	g->content = (t_command *)(cmd_line->content);
	g->tab = execution(g->content);
	g->ret = get_fd_in_and_out(g->content, &infile, &outfile);
	if (g->ret == -1)
		printf("error reading fdin or fdout\n");
	if (infile)
		g->fdin = infile;
	dup2(g->fdin, 0);
	close(g->fdin);
	if_last_command(cmd_line, &outfile, &(g->fdout), &(g->tmpout));
	if (cmd_line->next != NULL)
		wire_outfile(&(g->fdin), &(g->fdout), &outfile);
	dup2(g->fdout, 1);
	close(g->fdout);
	*print_promt() = 1;
	if (ft_strlen(g->tab[0]) != 0)
	{
		exec_child(g->tab, env);
	}
	ft_cleartab(&(g->tab));
}

int		execute_commands(t_list *cmd_line, char ***env)
{
	t_execute_commands g;

	if (!cmd_line)
		cmd_line = NULL;
	g.tmpin = dup(0);
	g.tmpout = dup(1);
	g.fdin = dup(g.tmpin);
	g.fdout = dup(g.tmpout);
	while (cmd_line)
	{
		execute_command(cmd_line, env, &g);
		cmd_line = cmd_line->next;
	}
	wait(&(g.status));
	dup2(g.tmpin, 0);
	dup2(g.tmpout, 1);
	close(g.tmpin);
	close(g.tmpout);
	return (1);
}
