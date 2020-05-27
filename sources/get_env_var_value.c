/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:37:57 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 18:18:06 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern		char **environ;

int			is_variable(char *var_name, char *var_line)
{
	int		len;

	len = ft_strlen(var_name);
	if (len > (int)ft_strlen(var_line))
		return (0);
	len--;
	while (len >= 0)
	{
		if (var_name[len] != var_line[len])
			return (0);
		len--;
	}
	return (1);
}

char		*dup_value(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	ret = ft_strdup((str + i));
	return (ret);
}

char		*get_env_var_value(char *var, char ***local_env)
{
	int		i;
	char	**env;

	i = 0;
	env = environ;
	if (local_env != NULL)
		env = *local_env;
	while (env[i] != NULL)
	{
		if (is_variable(var, env[i]))
			return (dup_value(env[i]));
		i++;
	}
	return (NULL);
}
