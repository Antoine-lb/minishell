/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 09:04:52 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/11 11:20:58 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		*print_promt(void)
{
	static int i;

	return (&i);
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (*print_promt() == 0)
			ft_putstr_fd("\n$> ", 1);
		else
			ft_putstr_fd("\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (*print_promt() == 1)
			ft_putstr_fd("quit [exit code: 3]\n", 1);
	}
}
