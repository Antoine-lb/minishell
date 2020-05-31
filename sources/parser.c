/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:24:30 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 08:57:31 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	parse(t_parser *psr, t_list **cmds,
t_list **cmd)
{
	t_command	*cmd_tmp;
	t_list		*last;
	t_list		*tmp;

	cmd_tmp = parse_cmd(psr->command, psr->sep);
	last = ft_lstlast(*cmd);
	if (ft_lstsize(*cmd) > 0 &&
	((t_command *)(last->content))->sep > 2 &&
	((t_command *)(last->content))->sep < 6)
	{
		parse_out(((t_command *)(last->content)), cmd_tmp);
		free(cmd_tmp->cmd);
		free(cmd_tmp);
	}
	else
	{
		cmd_tmp->redirections = NULL;
		tmp = ft_lstnew(cmd_tmp);
		ft_lstadd_back(cmd, tmp);
	}
	if (psr->sep == 1 || psr->sep == -1)
		parse_last(tmp, cmd, cmds);
	free(psr->command);
}
