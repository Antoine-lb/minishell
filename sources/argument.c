#include "../libft/libft.h"
#include "../includes/command.h"
#include <libc.h>

void	ft_pushstr(t_command *cmd, char **tmp)
{
	t_list	*lst;

	if ((*tmp) != NULL)
	{
		lst = ft_lstnew((void *)ft_strdup((*tmp)));
		ft_lstadd_back(&(cmd->args), lst);
		free((*tmp));
		(*tmp) = NULL;
	}
}

void	ft_openaall(t_cursor *csr, t_command *cmd, char **tmp, char *str)
{
	if ((int)(str[csr->b - 1]) != 92 || ((int)(str[csr->b - 2]) == 92 && (int)(str[csr->b]) == 39) || csr->b == 0)
	{
		if (csr->c == 0)
		{
			ft_pushstr(cmd, tmp);
			(*tmp) = ft_strnew();
		}
		csr->a = csr->b + 1;
		csr->c = 1;
	}
}

void	ft_opennorm(t_cursor *csr, t_command *cmd, char **tmp, char *str)
{
	char	*tp1;
	char	*tp2;

	csr->c = 1;
	csr->b = ft_getnnext(str, csr->b, ' ');
	if ((int)(str[csr->b]) == 92)
		csr->b++;
	if (csr->c == 0 && (*tmp) == NULL && (int)(str[csr->b]) == 32)
		(*tmp) = ft_strnew();
	tp1 = (*tmp);
	if (str[csr->b] == '$' && ((int)(str[csr->b - 1]) != 92 || ((int)(str[csr->b - 1]) == 92 && (int)(str[csr->b - 2]) == 92)))
	{
		tp2 = get_env_var_value(ft_substr(str, csr->b + 1, ft_getnext(str, csr->b, ' ') - csr->b));
		csr->b = ft_getnext(str, csr->b, ' ') - 1;
	}
	else
		tp2 = ft_substr(str, csr->b, 1);
	(*tmp) = ft_strjoin(tp1, tp2);
	free(tp1);
	free(tp2);
	if (((int)str[csr->b + 1]) == 32)
	{
		ft_pushstr(cmd, tmp);
		csr->c = 0;
	}
}

void	ft_closea39(t_cursor *csr, t_command *cmd, char **tmp, char *str)
{
	char	*tp1;
	char	*tp2;

	tp1 = (*tmp);
	tp2 = ft_substr(str, csr->a, csr->b - csr->a);
	(*tmp) = ft_strjoin(tp1, tp2);
	csr->a = -1;
	if ((int)(str[csr->b + 1]) == 32)
	{
		ft_pushstr(cmd, tmp);
		csr->c = 0;
	}
	free(tp1);
	free(tp2);
}

void	ft_closea34(t_cursor *csr, t_command *cmd, char **tmp, char *str)
{
	char	*tp1;
	char	*tp2;
	char	*tp3;
	char	*rep;
	int		from;

	tp1 = (*tmp);
	from = csr->a;
	if ((int)(str[from - 2]) == 92)
		from--;
	if ((int)(str[csr->b - 1]) == 92)
	{
		tp2 = ft_substr(str, from, csr->b - from - 1);
		csr->a = csr->b + 1;
	}
	else
	{
		tp2 = ft_substr(str, from, csr->b - from);
		csr->a = -1;
	}
	tp3 = ft_replaceby(tp2, '$');
	rep = ft_stripslashes(tp3, "\\$\'");
	(*tmp) = ft_strjoin(tp1, rep);
	if ((int)(str[csr->b + 1]) == 32)
	{
		ft_pushstr(cmd, tmp);
		csr->c = 0;
	}
	free(rep);
	free(tp1);
	free(tp2);
	free(tp3);
}
