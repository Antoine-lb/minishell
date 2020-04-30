/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 10:40:29 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 18:01:49 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_name(char *str) {
	int		a;

	a = 0;
	if (!ft_isalpha(str[0]))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	while (str[a]) {
		if ((str[a] == '+' && str[a + 1] != '=') || (str[a] == '=' && a == 0)) {
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		a++;
	}
	return (1);
}

int		variable_exists(char *new_var, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (is_same_var(new_var, env[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**dup_and_add_env(char *new_var, char **old_env)
{
	char	**ret_env;
	int		size;
	int		i;
	int		does_not_exist;

	i = 0;
	does_not_exist = 0;
	size = size_of_2d_array(old_env);
	if (!variable_exists(new_var, old_env))
		does_not_exist = 1;
	ret_env = (char **)malloc(sizeof(char *) * (size + 1 + does_not_exist));
	if (ret_env == NULL)
		return (NULL);
	while (i < size)
	{
		if (is_same_var(new_var, old_env[i]) && ft_strchr(new_var, '=') != NULL)
			ret_env[i] = ft_strdup(new_var);
		else
			ret_env[i] = ft_strdup(old_env[i]);
		i++;
	}
	if (does_not_exist)
		ret_env[i++] = ft_strdup(new_var);
	ret_env[i] = NULL;
	return (ret_env);
}

void	print_all(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(ft_substr(env[i], 0, ft_getnext(env[i], 0, '=')), 1);
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(ft_substr(env[i], ft_getnext(env[i], 0, '=') + 1, ft_getnext(env[i], 0, '\n')), 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int		bi_export(char **args, char ***env)
{
	char	**tmp;
	int		i;

	i = 1;
	while (args[i])
	{
		if (!ft_check_name(args[i]))
			return (-1);
		tmp = dup_and_add_env(args[i], *env);
		if (tmp == NULL)
			return (-1);
		free_2d_array(*env);
		*env = tmp;
		sort(*env);
		i++;
	}
	if (i == 1)
		print_all(*env);
	return (0);
}
