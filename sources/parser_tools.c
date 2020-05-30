/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:24:30 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 08:57:31 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/command.h"

void	parse_args(t_command *cmd, char *arg, char ***local_env)
{
	char			*tmp;
	t_cursor		csr;

	init_cursor(&tmp, &csr, arg);
	while (arg[csr.b++])
	{
		if (csr.a == -1)
		{
			if (csr.c == 0)
				csr.b = ft_ngetnnext(arg, csr.b, " \t");
			if ((int)(arg[csr.b]) == 39 || (int)(arg[csr.b]) == 34)
				ft_openaall(&csr, cmd, &tmp);
			else
				ft_opennorm(&csr, cmd, &tmp, local_env);
		}
		else
		{
			if ((int)(arg[csr.b]) == 39 && (int)(arg[csr.a - 1]) == 39)
				ft_closea39(&csr, cmd, &tmp);
			else if ((int)(arg[csr.b]) == 34 && (int)(arg[csr.a - 1]) == 34)
				ft_closea34(&csr, cmd, &tmp, local_env);
		}
	}
	ft_pushstr(cmd, &tmp);
}

void	parse_arg(t_command *cmd, char *line, char ***local_env)
{
	char	*tmp;
	char	*tmp2;
	char	*arg;

	tmp = ft_strtrim(line, " \t");
	if (tmp != NULL)
	{
		arg = ft_nstrchr(tmp, " \t");
		if (arg != NULL)
		{
			tmp2 = arg + 1;
			parse_args(cmd, tmp2, local_env);
		}
		free(tmp);
	}
}

void	parse_out(t_command *last, t_command *cmd)
{
	int				a;
	int				s;
	t_redirection	*red;
	t_list			*tmp;

	a = 1;
	s = ft_lstsize(cmd->args) + 1;
	red = (t_redirection *)malloc(sizeof(t_redirection));
	red->sep = last->sep;
	red->args = ft_strdup(cmd->cmd);
	while (a < s)
	{
		if (a == 1 && ft_strcmp(last->cmd, "") == 0)
			last_cmd(last, (char *)(cmd->args->content));
		else
			ft_lstadd_back(&(last->args),
			ft_lstnew(cmd->args->content));
		tmp = cmd->args->next;
		free(cmd->args);
		cmd->args = tmp;
		a++;
	}
	last->sep = cmd->sep;
	ft_lstadd_back(&((last)->redirections), ft_lstnew(red));
}

void	*parse_cmd(char *line, int sep, char ***local_env)
{
	t_command	*cmd;
	char		*tmp;

	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->args = NULL;
	tmp = ft_strtrim(line, " \t");
	cmd->cmd = ft_substr(tmp, 0, ft_ngetnext(tmp, 0, " \t"));
	free(tmp);
	cmd->sep = sep;
	parse_arg(cmd, line, local_env);
	return (cmd);
}

void	parse_last(t_list *tmp, t_list **cmd, t_list **cmds)
{
	tmp = ft_lstnew(*cmd);
	ft_lstadd_back(cmds, tmp);
	*cmd = NULL;
}
