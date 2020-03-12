/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:09:20 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 17:14:36 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort(char **arr)
{
	int		i;
	char	*tmp;
	int		done;

	i = 0;
	done = 0;
	while (!done)
	{
		done = 1;
		i = 0;
		while (arr[i] != NULL)
		{
			if (arr[i + 1] != NULL)
			{
				if (ft_strcmp(arr[i], arr[i + 1]) > 0)
				{
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
					done = 0;
				}
			}
			i++;
		}
	}
}
