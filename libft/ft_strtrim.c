/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 08:16:59 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/19 11:07:31 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_check(char c, char const *s)
{
	int		a;

	a = 0;
	while (s[a])
	{
		if (c == s[a])
			return (0);
		a++;
	}
	return (1);
}

static	int		ft_len(char const *s1, char const *set)
{
	size_t	a;
	size_t	b;

	a = ft_strlen(s1) - 1;
	b = 0;
	while (ft_check(s1[b], set) == 0)
		b++;
	if (b == ft_strlen(s1))
		return (-1);
	while (ft_check(s1[a], set) == 0)
	{
		a--;
		b++;
	}
	return (b);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	a;
	char	*b;
	size_t	c;
	size_t	d;

	c = 0;
	d = 0;
	if (!s1 && set)
		return (NULL);
	if (s1 && !set)
		return (ft_strdup(s1));
	if (!s1 && !set)
		return (NULL);
	a = ft_strlen(s1) - ft_len(s1, set);
	if (!(b = (char*)malloc(sizeof(char) * (a + 1))))
		return (NULL);
	if (ft_len(s1, set) == -1)
		a = 0;
	while (ft_check(s1[c], set) == 0)
		c++;
	while (d < a)
		b[d++] = s1[c++];
	b[d] = '\0';
	return (b);
}
