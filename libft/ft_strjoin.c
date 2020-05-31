/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:58:43 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/19 15:54:58 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_joined(char const *s1, char const *s2, char *c)
{
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (s1[a])
	{
		c[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		c[a + b] = s2[b];
		b++;
	}
	c[a + b] = '\0';
	return (c);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	int		b;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	b = ft_strlen(s1) + ft_strlen(s2);
	if ((!(a = (char*)malloc(sizeof(char) * (b + 1)))))
		return (NULL);
	a = ft_joined(s1, s2, a);
	return (a);
}
