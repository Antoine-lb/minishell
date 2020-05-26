/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_add_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 10:40:29 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 18:01:49 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*merge_variables(char *var_1, char *var_2)
{
	char	**var_2_split;
	char	*new_var;

	var_2_split = ft_split(var_2, '=');
	new_var = ft_strjoin(var_1, var_2_split[1]);
	free_2d_array(var_2_split);
	return (new_var);
}

void	merge_variable(char **new_env, char *old_env, char *new_var)
{
	if (ft_strchr(new_var, '+') != NULL)
		*new_env = merge_variables(old_env, new_var);
	else
		*new_env = ft_strdup(new_var);
}

char	**dup_and_add_env(char *new_var, char **old_env)
{
	char	**new_env;
	int		size;
	int		i;
	int		does_not_exist;

	i = 0;
	does_not_exist = 0;
	size = size_of_2d_array(old_env);
	if (!variable_exists(new_var, old_env))
		does_not_exist = 1;
	new_env = (char **)malloc(sizeof(char *) * (size + 1 + does_not_exist));
	if (new_env == NULL)
		return (NULL);
	while (i < size)
	{
		if (is_same_var(new_var, old_env[i]) && ft_strchr(new_var, '=') != NULL)
			merge_variable(&new_env[i], old_env[i], new_var);
		else
			new_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	if (does_not_exist)
		new_env[i++] = ft_strdup(new_var);
	new_env[i] = NULL;
	return (new_env);
}
