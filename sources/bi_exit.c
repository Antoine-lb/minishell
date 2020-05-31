/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 09:13:35 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/30 12:13:17 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		exit_edge_cases(char **args, int nb)
{
	long long int	arg;

	arg = ft_atoi(args[1]);
	if (nb == 1)
	{
		if (arg >= 0 && arg <= 9223372036854775807)
			exit(arg % 256);
	}
	else
	{
		if (arg < 0 && arg > -9223372036854775807)
			exit(arg % 255);
		if (arg - 1 == 9223372036854775807)
			exit(0);
	}
	return (0);
}

void	bi_exit(char **args, char ***env)
{
	int				nb;

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
	if ((nb = ft_isnumber(args[1])) != 0)
	{
		exit_edge_cases(args, nb);
	}
	exit(2);
}
