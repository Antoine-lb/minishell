/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_same_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:24:27 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 17:33:42 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_same_var(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] && str1[i] != '=' && str2[i]
		&& str2[i] != '=' && str1[i] == str2[i])
	{
		i++;
	}
	if ((!str1[i] || str1[i] == '=') && (!str2[i] || str2[i] == '='))
	{
		return (1);
	}
	return (0);
}
