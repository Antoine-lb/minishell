/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <gsharony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:31:09 by gsharony          #+#    #+#             */
/*   Updated: 2020/02/24 09:17:49 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr(const char *s, int c)
{
	size_t	a;

	a = -1;
	while (++a < ft_strlen(s) + 1)
		if (*(s + a) == (char)c)
			return ((char *)(s + a));
	return (NULL);
}

int			ft_linelen(char *str)
{
	int		a;

	a = 0;
	while (str[a] != '\n' && str[a])
		a++;
	return (a);
}

char		*get_line(char *content)
{
	if (ft_strchr(content, '\n'))
	{
		ft_strcpy(content, ft_strchr(content, '\n') + 1);
		return (content);
	}
	return (NULL);
}

char		*ft_strcpy(char *dest, const char *src)
{
	unsigned int a;

	a = 0;
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}
