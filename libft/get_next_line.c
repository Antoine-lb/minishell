/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:25:51 by gsharony          #+#    #+#             */
/*   Updated: 2020/03/12 11:22:29 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(void)
{
	char	*a;

	if (!(a = (char *)malloc(sizeof(char) * (1))))
		return (NULL);
	a[0] = '\0';
	return (a);
}

int		output(char **content, char **line)
{
	*line = ft_substr(*content, 0, ft_linelen(*content));
	if (get_line(*content) == NULL)
	{
		ft_putstr_fd("exit\n", 0);
		free(*content);
		*content = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*content;
	int				read_output;
	char			*tmp;

	if ((!content && (content = ft_strnew()) == NULL) ||
	fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (-1);
	while (!(ft_strchr(content, '\n')) &&
	((read_output = read(fd, buffer, BUFFER_SIZE)) > 0 || read_output == 0))
	{
		if (ft_strlen(content) == 0 && read_output == 0)
			break ;
		else
		{
			buffer[read_output] = '\0';
			tmp = content;
			content = ft_strjoin(tmp, buffer);
			free(tmp);
		}
	}
	return (output(&content, line));
}
