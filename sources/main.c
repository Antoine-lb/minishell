#include "../includes/minishell.h"

int		rep(void)
{
	int			ret;
	int			cnt;
	char		*line;
	t_parser	cmd;

	cnt = 1;
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	while ((cmd = command(&line, cnt)).sep > -1)
	{
		parse(cmd);
		cnt++;
	}
	parse(cmd);
	return (ret);
}

int		main(void)
{
	while (rep() > 0);
	return (0);
}
