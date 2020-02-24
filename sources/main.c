#include "../includes/minishell.h"

int		rep(void)
{
	int		ret;
	char	*line;
	char	buf[51];

	ft_putstr_fd(ft_strrchr(getcwd(buf, 50), '/') + 1, 1);
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	command(line);
	free(line);
	return (ret);
}

int		main(void)
{
	while (rep() > 0);
	return (0);
}
