#include <libc.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

int		rep(void)
{
	int		ret;
	char	*line;
	char	buf[51];

	ft_putstr_fd(ft_strrchr(getcwd(buf, 50), '/') + 1, 1);
	ft_putstr_fd("# ", 1);
	ret = get_next_line(0, &line);
	free(line);
	return (ret);
}

int		main(void)
{
	while (rep() > 0);
	return (0);
}
