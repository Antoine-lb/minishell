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
	int					cmd;
	t_list				*args;
	int					sep;
}						t_command;

t_parser				command(char **line, int nb);

void					parse(t_parser psr, t_command *cmd);

void					init_cursor(t_cursor *csr);
void					init_parser(t_parser *psr);

void					instring(int *a, char c);

#endif
