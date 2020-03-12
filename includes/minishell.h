/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:08:19 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 11:24:50 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <libc.h>
#include "../libft/libft.h"
#include "./command.h"
#include <signal.h>

char *get_path_from_env(char *cmd);
int *print_promt(void);
void handle_sig(int sig);
int execute_commands(t_list *cmd_line, char ***env);
char **dup_env(char **real_env);
void bi_env(char **env);
int		bi_export(char **args, char ***env);
int		size_of_2d_array(char **env);

#endif
