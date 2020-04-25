#include "../libft/libft.h"
#include "../includes/command.h"

char *ft_merge(char *str, int a, int b, char ***local_env)
{
	char *tp1;
	char *tp2;
	char *var;
	char *tmp;

	tp1 = ft_substr(str, a, b - a);
	tp2 = ft_substr(str, b + 1, ft_getnext(str, b + 1, ' ') - (b + 1));
	var = get_env_var_value(tp2, local_env);
	tmp = ft_strjoin(tp1, var);
	free(tp1);
	free(tp2);
	free(var);
	return (tmp);
}

char *ft_replaceby(char *str, char c, char ***local_env)
{
	char *tmp;
	char *tmp2;
	char *cons;
	int a;
	int b;

	a = 0;
	b = 0;
	cons = ft_strnew();
	while (str[b])
	{
		if (str[b] == c && (((int)(str[b - 1]) != 92) || ((int)(str[b - 1]) == 92 && (int)(str[b - 2]) == 92)))
		{
			tmp = cons;
			tmp2 = ft_merge(str, a, b, local_env);
			cons = ft_strjoin(tmp, tmp2);
			a = ft_getnext(str, b, ' ');
			free(tmp2);
			free(tmp);
		}
		b++;
	}
	if (a != 0)
	{
		tmp = cons;
		tmp2 = ft_strdup(str + a);
		cons = ft_strjoin(tmp, tmp2);
		free(tmp2);
		free(tmp);
		return (cons);
	}
	free(cons);
	return (ft_strdup(str));
}