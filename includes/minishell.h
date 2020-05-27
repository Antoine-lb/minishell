/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:08:19 by ale-baux          #+#    #+#             */
/*   Updated: 2020/04/04 15:59:25 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "../libft/libft.h"
# include "./command.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define CWD_BUFFER_SIZE 1000

typedef struct			s_execute_commands
{
	int					status;
	char				**tab;
	t_command			*content;
	int					tmpin;
	int					tmpout;
	int					fdin;
	int					fdout;
	int					ret;
}						t_execute_commands;

int						*print_promt(void);
int						is_same_var(char *str1, char *str2);
int						variable_exists(char *new_var, char **env);
int						last_exit_code(int val);
int						update_pwd(char ***env);
int						add_path_at_the_end(char ***env);
int						get_fd_in_and_out(t_command *content,
int *fdin, int *fdout);
int						execute_commands(t_list *cmd_line, char ***env);
int						size_of_2d_array(char **env);
int						bi_cd(char **args, char ***env);
int						bi_echo(char **args);
int						bi_pwd(char ***env);
int						bi_export(char **args, char ***env);
int						bi_unset(char **args, char ***env);
void					bi_env(char **env);
void					bi_exit(char **args, char ***env);
void					sort(char **arr);
void					free_2d_array(char **arr);
void					exec_child(char **args, char ***env);
void					handle_sig(int sig);
char					**dup_env(char **real_env);
char					**dup_and_add_env(char *new_var, char **old_env);
char					*get_path_from_env(char *cmd, char ***env);

#endif
