#include "../includes/minishell.h"

int		rep(void)
{
	int			ret;
	int			cnt;
	char		*line;
	t_command	*cmd_tmp;
	t_parser	cmd_text;

	cnt = 1;
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	while ((cmd_text = command(&line, cnt)).sep > -1)
	{
		cmd_tmp = (t_command *)malloc(sizeof(t_command));
		parse(cmd_text, &cmd_tmp);
		free(cmd_tmp);
		cnt++;
	}
	cmd_tmp = (t_command *)malloc(sizeof(t_command));
	parse(cmd_text, &cmd_tmp);
	free(cmd_tmp);
	return (ret);
}

int		main(void)
{
	while (rep() > 0);
	return (0);
}
