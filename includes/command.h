#ifndef COMMAND_H
# define COMMAND_H
# include "../libft/libft.h"

typedef struct			s_cursor
{
	int					a;
	int					b;
	int					c;
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

int						command(t_parser **psr, char **line, int nb);

void					parse(int sep, char *line, t_list **cmds, t_list **cmd);

void					init_cursor(char **tmp, t_cursor *csr);
void					init_parser(t_parser *psr);

void					instring(char *str, int *a, int b);
void					ft_closea34(t_cursor *csr, t_command *cmd, char **tmp, char *str);
void					ft_closea39(t_cursor *csr, t_command *cmd, char **tmp, char *str);
void					ft_opennorm(t_cursor *csr, t_command *cmd, char **tmp, char *str);
void					ft_openaall(t_cursor *csr, t_command *cmd, char **tmp, char *str);
void					ft_pushstr(t_command *cmd, char **tmp);
char					**execution(t_command *cmd);
char 					*get_env_var_value(char *var);
char					*ft_replaceby(char *str, char c);

#endif
