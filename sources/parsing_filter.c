#include "../includes/minishell.h"

char	**execution(t_command *cmd)
{
	int a;
	char **tab;

	a = ft_lstsize(cmd->args) + 1;
	tab = (char **)malloc(sizeof(char *) * (a + 1));
	tab[0] = cmd->cmd;
	a = 1;
	while (cmd->args)
	{
		tab[a] = (char *)cmd->args->content;
		cmd->args = cmd->args->next;
		a++;
	}
	tab[a] = NULL;
	return (tab);
}
