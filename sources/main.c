#include "../includes/minishell.h"

void	print_cmd(void *cmd)
{
	// printf("cmd = %d\n", ((t_command *)cmd)->cmd);
	printf("here in iter\n");
}

int		rep(void)
{
	int			ret;
	int			cnt;
	char		*line;
	t_parser	cmd_text;
	t_list		*cmd_beginning;
	t_command	*cmd_tmp;

	cmd_beginning = (t_list *)malloc(sizeof(t_list) * 1);
	cmd_beginning->next = NULL;
	cnt = 1;
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	while ((cmd_text = command(&line, cnt)).sep > -1)
	{
		cmd_tmp = (t_command *)malloc(sizeof(t_command) * 1);
		parse(cmd_text, cmd_tmp);
		ft_lstadd_back(&(cmd_beginning), ft_lstnew(cmd_tmp));
		cnt++;
	}
	parse(cmd_text, cmd_tmp);
	ft_lstiter(cmd_beginning, print_cmd);
	return (ret);
}

int		main(void)
{
	while (rep() > 0);
	return (0);
}
