#include "../libft/libft.h"
#include "../includes/command.h"

void		ft_pushstr(t_command *cmd, char **tmp)
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

void		ft_openaall(t_cursor *csr, t_command *cmd, char **tmp)
{
	if ((int)(csr->str[csr->b - 1]) != 92 || ((int)(csr->str[csr->b - 2]) == 92
	&& (int)(csr->str[csr->b]) == 39) || csr->b == 0)
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

void		ft_opennorm(t_cursor *csr, t_command *cmd,
char **tmp, char ***local_env)
{
	char	*tp1;
	char	*tp2;

	csr->c = 1;
	csr->b = ft_ngetnnext(csr->str, csr->b, " \t");
	if ((int)(csr->str[csr->b]) == 92)
		csr->b++;
	if (csr->c == 0 && (*tmp) == NULL && ft_includes(csr->str[csr->b], " \t"))
		(*tmp) = ft_strnew();
	tp1 = (*tmp);
	tp2 = ft_substr(csr->str, csr->b, 1);
	(*tmp) = ft_strjoin(tp1, tp2);
	free(tp1);
	free(tp2);
	if (((int)csr->str[csr->b]) == 0 ||
	ft_includes(csr->str[csr->b + 1], " \t"))
	{
		ft_pushstr(cmd, tmp);
		csr->c = 0;
	}
}

void		ft_closea39(t_cursor *csr, t_command *cmd, char **tmp)
{
	char	*tp1;
	char	*tp2;

	tp1 = (*tmp);
	tp2 = ft_substr(csr->str, csr->a, csr->b - csr->a);
	(*tmp) = ft_strjoin(tp1, tp2);
	csr->a = -1;
	if (ft_includes(csr->str[csr->b + 1], " \t"))
	{
		ft_pushstr(cmd, tmp);
		csr->c = 0;
	}
	free(tp1);
	free(tp2);
}

void		ft_closea34(t_cursor *csr, t_command *cmd,
char **tmp, char ***local_env)
{
	char	*tp1;
	char	*tp2;
	char	*rep;
	int		from;

	tp1 = (*tmp);
	from = csr->a;
	if ((int)(csr->str[csr->b - 1]) == 92)
		tp2 = ft_substr(csr->str, from, csr->b - from - 1);
	else
		tp2 = ft_substr(csr->str, from, csr->b - from);
	if ((int)(csr->str[csr->b - 1]) == 92)
		csr->a = csr->b + 1;
	else
		csr->a = -1;
	rep = ft_stripslashes(tp2, "\\$\'");
	(*tmp) = ft_strjoin(tp1, rep);
	if (ft_includes(csr->str[csr->b + 1], " \t"))
	{
		ft_pushstr(cmd, tmp);
		csr->c = 0;
	}
	free(rep);
	free(tp1);
	free(tp2);
}
