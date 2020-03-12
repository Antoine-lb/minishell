/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 10:40:29 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 11:15:05 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **dup_and_add_env(char *new_var, char **old_env)
{
	char **ret_env;
	int		size;
	int i;

	i = 0;
	size = size_of_2d_array(old_env);
	ret_env = (char**)malloc(sizeof(char*) * (size + 2));
	if (ret_env ==NULL)
		return (NULL);
	while (i < size)
	{
		ret_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	ret_env[i] = ft_strdup(new_var);
	i++;
	ret_env[i] = NULL;
	return (ret_env);
}

char **		bi_export(char **args, char ***env)
{
	char ** tmp;
	printf("args[1] = %s\n", args[1]);
	*env = dup_and_add_env(args[1], *env);
	bi_env(*env);
	// env = &tmp;
	// free old
	return (dup_and_add_env(args[1], *env));
}