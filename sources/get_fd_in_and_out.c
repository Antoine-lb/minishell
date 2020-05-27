/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_in_and_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 09:13:35 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/30 12:13:17 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_last_symbol(t_list *redirections, int target)
{
	int	sep;

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

int		get_fd_in_and_out_norm(int sep, int *fdin, int *fdout, t_list *r)
{
	if (sep == 3)
	{
		*fdin = open(((t_redirection *)(r->content))->args, O_RDONLY, 0666);
		if (!is_last_symbol(r, 3))
			close(*fdin);
	}
	else if (sep == 4)
	{
		*fdout = open(((t_redirection *)(r->content))->args,
			O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (!is_last_symbol(r, 4) || !is_last_symbol(r, 5))
			close(*fdout);
	}
	else if (sep == 5)
	{
		*fdout = open(((t_redirection *)(r->content))->args,
			O_RDWR | O_CREAT | O_APPEND, 0666);
		if (!is_last_symbol(r, 4) || !is_last_symbol(r, 5))
			close(*fdout);
	}
	return (0);
}

int		get_fd_in_and_out(t_command *content, int *fdin, int *fdout)
{
	t_list	*redirections;
	int		input_has_changed;
	int		sep;

	input_has_changed = 0;
	redirections = content->redirections;
	while (redirections)
	{
		sep = (int)((t_redirection *)(redirections->content))->sep;
		get_fd_in_and_out_norm(sep, fdin, fdout, redirections);
		redirections = redirections->next;
	}
	return (input_has_changed);
}
