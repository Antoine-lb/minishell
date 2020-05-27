#include "../libft/libft.h"
#include "../includes/command.h"

void	ft_setvariable(char **var, char *buf)
{
	char	*tmp;

	tmp = *var;
	*var = ft_strjoin(tmp, buf);
	free(tmp);
}

void	ft_nonvariable(char **str, t_parser **psr)
{
	char	*tmp;

	tmp = ft_strdup("\\$");
	*str = ft_strjoin((*psr)->command, tmp);
	free(tmp);
}

void	ft_putvariable(char **str, t_parser **psr, char **var, char ***env)
{
	char	*tmp;

	tmp = get_env_var_value(*var, env);
	*str = ft_strjoin((*psr)->command, tmp);
	free(tmp);
}

void	ft_putnormal(char **tmp, t_parser **psr, char *buf, int *escape)
{
	if (*escape == 0)
	{
		*tmp = ft_strjoin((*psr)->command, buf);
		free((*psr)->command);
		(*psr)->command = *tmp;
	}
	else
		*escape = 0;
}

void	ft_retnormal(t_parser **psr, int *b)
{
	char	*tmp;

	tmp = (*psr)->command;
	(*psr)->command = ft_strtrim(tmp, " \t");
	(*psr)->sep = -1;
	*b = 0;
	free(tmp);
}
