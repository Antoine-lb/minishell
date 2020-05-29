/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guysharony <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 15:59:43 by guysharon         #+#    #+#             */
/*   Updated: 2020/04/04 15:59:50 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "../libft/libft.h"

typedef struct			s_cursor
{
	int					a;
	int					b;
	int					c;
	char				*str;
}						t_cursor;

typedef struct			s_parser
{
	int					sep;
	char				*command;
}						t_parser;

typedef struct			s_redirection
{
	int					sep;
	char				*args;
}						t_redirection;

typedef struct			s_command
{
	char				*cmd;
	t_list				*args;
	t_list				*redirections;
	int					sep;
}						t_command;

int						last_exit_code(int val);
void					initparser(t_parser **psr);
int						checker(char **line, t_parser **psr, char ***env);
void					bcommand(t_parser **psr, char **line,
char ***env, int *a);
int						ft_string(char *str, int b);
void					ft_parser(t_parser **psr, char ***env, char c, int d);
void					ft_retnormal(t_parser **psr, int *b);
void					ft_putnormal(char **tmp, t_parser **psr,
char *buf, int *escape);
void					ft_putvariable(char **str, t_parser **psr,
char **var, char ***env);
void					ft_nonvariable(char **str, t_parser **psr);
void					ft_setvariable(char **var, char *buf);
int						rcommand2(t_parser **psr,
char **line, int a, int *b);
int						rcommand(t_parser **psr, char **line, int a, int *b);
int						command(t_parser **psr, char **line, char ***env);
void					parse_out(t_command *last, t_command *cmd);
void					parse_last(t_list *tmp, t_list **cmd, t_list **cmds);
void					*parse_cmd(char *line, int sep, char ***local_env);
void					parse_arg(t_command *cmd, char *line,
char ***local_env);
void					parse(t_parser *psr, t_list **cmds,
t_list **cmd, char ***local_env);
void					init_cursor(char **tmp, t_cursor *csr, char *str);
void					init_parser(t_parser *psr);
void					instring(char *str, int *a, int b);
void					ft_closea34(t_cursor *csr, t_command *cmd,
char **tmp, char ***local_env);
void					ft_closea39(t_cursor *csr, t_command *cmd,
char **tmp);
void					ft_opennorm(t_cursor *csr, t_command *cmd,
char **tmp, char ***local_env);
void					ft_openaall(t_cursor *csr, t_command *cmd,
char **tmp);
void					ft_pushstr(t_command *cmd, char **tmp);
char					**execution(t_command *cmd);
char					*get_env_var_value(char *var, char ***local_env);

#endif
