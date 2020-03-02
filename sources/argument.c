#include "../libft/libft.h"
#include "../includes/command.h"

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

void	ft_openaall(t_cursor *csr,  int *c, t_command *cmd, char **tmp, char *str)
{
	if ((int)(str[csr->b - 1]) != 92 || ((int)(str[csr->b - 2]) == 92 && (int)(str[csr->b]) == 39) || csr->b == 0)
	{
		if ((*c) == 0)
		{
			ft_pushstr(cmd, tmp);
			(*tmp) = ft_strnew();
		}
		csr->a = csr->b + 1;
		(*c) = 1;
	}
}

void	ft_opennorm(t_cursor *csr, int *c, t_command *cmd, char **tmp, char *str)
{
	char	*tp1;
	char	*tp2;

	if ((int)(str[csr->b]) == 92)
		csr->b++;
	if ((*c) == 0 && (*tmp) == NULL && (int)(str[csr->b]) != 92)
		(*tmp) = ft_strnew();
	tp1 = (*tmp);
	tp2 = ft_substr(str, csr->b, 1);
	(*tmp) = ft_strjoin(tp1, tp2);
	free(tp1);
	free(tp2);
	if (((int)str[csr->b + 1]) == 32)
		ft_pushstr(cmd, tmp);
}

void	ft_closea39(t_cursor *csr, int *c, t_command *cmd, char **tmp, char *str)
{
	char	*tp1;
	char	*tp2;

	tp1 = (*tmp);
	tp2 = ft_substr(str, csr->a, csr->b - csr->a);
	(*tmp) = ft_strjoin(tp1, tp2);
	csr->a = -1;
	if ((int)(str[csr->b + 1]) != 92)
	{
		ft_pushstr(cmd, tmp);
		(*c) = 0;
	}
	free(tp1);
	free(tp2);
}

void	ft_closea34(t_cursor *csr, int *c, t_command *cmd, char **tmp, char *str)
{
	char	*tp1;
	char	*tp2;

	tp1 = (*tmp);
	if ((int)(str[csr->b - 1]) == 92)
	{
		tp2 = ft_substr(str, csr->a, csr->b - csr->a - 1);
		(*tmp) = ft_strjoin(tp1, tp2);
		free(tp1);
		free(tp2);
		tp1 = (*tmp);
		tp2 = ft_substr(str, csr->b, 1);
		(*tmp) = ft_strjoin(tp1, tp2);
		csr->a = csr->b + 1;
	}
	else if ((int)(str[csr->b - 1]) != 92)
	{
		tp2 = ft_substr(str, csr->a, csr->b - csr->a);
		(*tmp) = ft_strjoin(tp1, tp2);
		ft_pushstr(cmd, tmp);
		csr->a = -1;
		(*c) = 0;
	}
	free(tp1);
	free(tp2);
}
