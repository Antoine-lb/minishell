/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:39:25 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 18:15:12 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dup_and_remove_var(char *remove_var, char **old_env)
{
	char	**ret_env;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = size_of_2d_array(old_env);
	ret_env = (char **)malloc(sizeof(char *) * (size));
	if (ret_env == NULL)
		return (NULL);
	while (i < size)
	{
		if (!is_same_var(remove_var, old_env[i]))
		{
			ret_env[j] = ft_strdup(old_env[i]);
			j++;
		}
		i++;
	}
	ret_env[j] = NULL;
	return (ret_env);
}

int		bi_unset(char **args, char ***env)
{
	char	**tmp;
	int		i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') != NULL)
		{
			printf("error: not valid identifier\n");
			return (-1);
		}
		if (variable_exists(args[i], *env))
		{
			tmp = dup_and_remove_var(args[i], *env);
			if (tmp == NULL)
				return (-1);
			free_2d_array(*env);
			*env = tmp;
		}
		i++;
	}
	return (0);
}
