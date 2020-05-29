/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_return.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:24:30 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 08:57:31 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/command.h"

int		ecommand1(t_parser **psr, char **line, int a)
{
	char	*tmp;
	int		error;

	error = 0;
	tmp = ft_strtrim((*psr)->command, " \t");
	if ((ft_strlen(tmp) == 0 &&
	ft_includes((*line)[ft_ngetnnext((*line), a + 1, " \t")], ";|<>")))
	{
		ft_putstr_fd("minishell: syntax error\n", 0);
		error = 1;
	}
	free(tmp);
	return (error);
}

int		ecommand2(char **line, int c)
{
	char	*tmp;
	int		error;

	error = 0;
	tmp = ft_strtrim((*line), " \t");
	if (((ft_includes(tmp[0], ";|")) && c < 3))
	{
		ft_putstr_fd("minishell: syntax error\n", 0);
		error = 1;
	}
	free(tmp);
	return (error);
}

int		ecommand3(char **line, int a)
{
	char	*tmp;
	int		error;

	error = 0;
	tmp = ft_strdup(*line);
	if (ft_includes(tmp[a], ";|<>") &&
	(ft_includes(tmp[ft_ngetnnext(tmp, a + 1, " \t")], ";|") ||
	ft_includes(tmp[ft_ngetnnext(tmp, a + 2, " \t")], "<>")))
	{
		ft_putstr_fd("minishell: syntax error\n", 0);
		error = 1;
	}
	free(tmp);
	return (error);
}

int		rcommand(t_parser **psr, char **line, int a, int *b)
{
	int		c;

	if ((c = ft_getnext(";|<>", 0, (*line)[a])) < 4 && (*line)[a - 1] != 92)
	{
		if (c == 3 && (*line)[a + 1] == '>')
			c = 4;
		(*psr)->sep = c;
		if (c == 4)
			a++;
		*b = a + 1;
		(*psr)->sep++;
		return (1);
	}
	return (0);
}

int		rcommand2(t_parser **psr, char **line, int a, int *b)
{
	int		c;

	if ((c = ft_getnext(";|<>", 0, (*line)[a])) < 4 && (*line)[a - 1] != 92)
	{
		if (ecommand1(psr, line, a) || ecommand2(line, c) || ecommand3(line, a))
		{
			last_exit_code(2);
			free((*psr)->command);
			free(*psr);
			free(*line);
			return (1);
		}
	}
	return (0);
}
