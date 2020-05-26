/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 09:13:35 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/30 12:13:17 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	bi_echo(char **args)
{
	int	a;
	int	b;

	a = 1;
	b = 1;
	while (args[a] != NULL && ft_strcmp(args[a], "-n") == 0)
	{
		b = 0;
		a++;
	}
	while (args[a])
	{
		ft_putstr_fd(args[a], 1);
		if (args[a + 1] != NULL)
			ft_putchar_fd(' ', 1);
		a++;
	}
	if (b == 1)
		ft_putchar_fd('\n', 1);
	return (1);
}
