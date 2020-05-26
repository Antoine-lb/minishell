/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 09:31:29 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 17:16:55 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		size_of_2d_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**dup_env(char **real_env)
{
	char	**ret_env;
	int		size;
	int		i;

	i = 0;
	size = size_of_2d_array(real_env);
	ret_env = (char**)malloc(sizeof(char*) * (size + 1));
	if (ret_env == NULL)
		return (NULL);
	while (i < size)
	{
		ret_env[i] = ft_strdup(real_env[i]);
		i++;
	}
	ret_env[i] = NULL;
	return (ret_env);
}
