#include "../includes/minishell.h"

char			**execution(t_command *cmd)
{
	int			a;
	char		**tab;
	t_command	*cmds;
	t_list		*tmp;

	cmds = cmd;
	a = ft_lstsize(cmds->args) + 1;
	tab = (char **)malloc(sizeof(char *) * (a + 1));
	tab[0] = ft_strdup(cmds->cmd);
	a = 1;
	while (cmds->args)
	{
		tmp = cmds->args;
		tab[a] = ft_strdup((char *)tmp->content);
		cmds->args = tmp->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
		a++;
	}
	tab[a] = NULL;
	return (tab);
}
