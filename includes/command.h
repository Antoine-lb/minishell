#ifndef COMMAND_H
# define COMMAND_H
# include "../libft/libft.h"

typedef struct			s_cursor
{
	int					a;
	int					b;
}						t_cursor;

typedef struct			s_parser
{
	int					sep;
	char				*command;
}						t_parser;

typedef struct			s_command
{
	char				*cmd;
	t_list				*args;
	int					sep;
}						t_command;

t_parser				command(char **line, int nb);

void					parse(t_parser psr, t_command *cmd);

void					init_cursor(char **tmp, t_cursor *csr, int *c);
void					init_parser(t_parser *psr);

void					instring(char *str, int *a, int b);
void					ft_closea34(t_cursor *csr, int *c, t_command *cmd, char **tmp, char *str);
void					ft_closea39(t_cursor *csr, int *c, t_command *cmd, char **tmp, char *str);
void					ft_opennorm(t_cursor *csr, int *c, t_command *cmd, char **tmp, char *str);
void					ft_openaall(t_cursor *csr,  int *c, t_command *cmd, char **tmp, char *str);
void					ft_pushstr(t_command *cmd, char **tmp);

#endif
