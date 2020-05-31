/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:24:30 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 08:57:31 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/command.h"

int		checker(char **line, t_parser **psr, char ***env)
{
	int				a;
	static int		b;
	int				d;

	a = b;
	d = 0;
	initparser(psr);
	while ((*line)[a] != '\0')
	{
		if ((d = ft_string(*line, a)) == 0)
		{
			if (rcommand2(psr, line, a))
				return (1);
			bcommand(psr, line, env, &a);
		}
		else
			ft_parser(psr, env, (*line)[a], d);
		a++;
	}
	ft_parser(psr, env, (*line)[a], d);
	if ((*line)[a] != '\0')
		ft_parser(psr, env, (*line)[a + 1], d);
	free((*psr)->command);
	return (0);
}

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
