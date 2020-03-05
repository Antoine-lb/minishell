#include "../includes/minishell.h"

char **execution(t_command *cmd)
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

int is_redirector(char *str)
{
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0)
	{
		return (1);
	}
	return (0);
}

t_list *duplicate_element(t_list *element)
{
	t_list *element_dup;
	element_dup = (t_list *)malloc(sizeof(t_list) * 1);
	element_dup->content = ft_strdup(element->content);
	element_dup->next = NULL;
	return (element_dup);
}

t_command *filter_cmd(t_command *cmd)
{
	t_list *all;
	t_list *element_dup;
	t_list *args;
	t_list *redirections;

	all = cmd->args;
	args = NULL;
	redirections = NULL;
	while (all)
	{
		element_dup = duplicate_element(all);
		if (is_redirector(all->content))
		{
			if (all->next != NULL)
			{
				ft_lstadd_back(&redirections, element_dup);
				// printf("added = [%s] and", element_dup->content);
				all = all->next;
				if (is_redirector(all->content))
				{
					printf("error: multiple redirections\n");
					return (NULL);
				}
				else
				{
					element_dup = duplicate_element(all);
					ft_lstadd_back(&redirections, element_dup);
					// printf(" [%s] to redirections\n", element_dup->content);
				}
			}
			else
			{
				printf("error: no file given\n");
				return (NULL);
			}
		}
		else
		{
			ft_lstadd_back(&args, element_dup);
			// printf("added [%s] to args\n", element_dup->content);
		}
		all = all->next;
	}

	t_command *new_cmd = (t_command *)malloc(sizeof(t_command) * 1);
	new_cmd->cmd = ft_strdup(cmd->cmd);
	new_cmd->args = args;
	new_cmd->redirections = redirections;

	// while(args)
	// {
	// 	printf("args->content = %s\n", args->content);
	// 	args= args->next;
	// }
	// while(redirections)
	// {
	// 	printf("redirections->content = %s\n", redirections->content);
	// 	redirections= redirections->next;
	// }
	return (new_cmd);
}