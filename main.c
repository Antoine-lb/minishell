#include <libc.h>

int		get_next_line(int fd, char **line);

int		rep(void)
{
	int		ret;
	char	*line;

	write(1, "minishell# ", 11);
	ret = get_next_line(0, &line);
	free(line);
	return (ret);
}

int		main(void)
{
	while (rep() > 0);
	return (0);
}
