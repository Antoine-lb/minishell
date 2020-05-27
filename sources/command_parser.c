#include "../libft/libft.h"
#include "../includes/command.h"

void	ft_isvariable(char **var, t_parser **psr, char *c, char ***env)
{
	char	*tmp1;
	char	*tmp2;

	if (ft_strcmp(*var, "\0") == 0 && *c == '?')
	{
		tmp2 = ft_itoa(last_exit_code(-1));
		tmp1 = ft_strjoin((*psr)->command, tmp2);
		free(tmp2);
	}
	else
	{
		if ((*c == '=' || *c == 34) && ft_strlen(*var) == 0)
			ft_nonvariable(&tmp1, psr);
		else
			ft_putvariable(&tmp1, psr, var, env);
	}
	free((*psr)->command);
	(*psr)->command = tmp1;
	free(*var);
	*var = NULL;
}

void	ft_parser(t_parser **psr, char ***env, char c, int d)
{
	char			*tmp;
	char			buf[2];
	static int		escape;
	static char		*var;
	int				size;

	buf[0] = c;
	buf[1] = '\0';
	size = ft_strlen((*psr)->command) - 1;
	if (var != NULL && d != 39)
	{
		if (!ft_isalnum(c) && c != '_')
		{
			if (ft_strcmp(var, "\0") == 0 && c == '?')
				escape = 1;
			ft_isvariable(&var, psr, &c, env);
		}
		else
			ft_setvariable(&var, buf);
	}
	if (c == '$' && ((*psr)->command)[size] != 92 && d != 39)
		var = ft_strdup("");
	else if (var == NULL && c != '\0')
		ft_putnormal(&tmp, psr, buf, &escape);
}
