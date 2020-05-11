/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 10:40:29 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 18:01:49 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     update_pwd(char ***env)
{
    char *buf;
    char **export_arg;

    export_arg = (char**)malloc(3 * sizeof(char**));
    export_arg[0] = NULL;
    export_arg[2] = NULL;

    buf = get_env_var_value("PWD", env);
    export_arg[1] = ft_strjoin("OLDPWD=", buf);
    free(buf);
    bi_export(export_arg, env);
    free(export_arg[1]);

    buf = (char *)malloc(sizeof(char) * CWD_BUFFER_SIZE);
    getcwd(buf, CWD_BUFFER_SIZE);
    export_arg[1] = ft_strjoin("PWD=", buf);
    bi_export(export_arg, env);
    free(buf);
    free(export_arg[1]);
    free(export_arg);

    return (0);
}

int		bi_pwd(char ***env)
{
    char *var_value;

    var_value = get_env_var_value("PWD", env);
    ft_putstr_fd(var_value, 1);
    ft_putstr_fd("\n", 1);
    free(var_value);
	return (0);
}
