/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:57:59 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/19 07:27:11 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordlen(char const *s, char c)
{
	int		a;
	int		b;

	a = 0;
	b = 0;
	while (s[b])
	{
		while (s[b] && (s[b] == c))
			b++;
		if (s[b] && s[b] != c)
		{
			a++;
			while (s[b] && s[b] != c)
				b++;
		}
	}
	return (a);
}

static char		*ft_cword(char const *s, char c)
{
	char	*a;
	int		b;

	b = 0;
	while (s[b] && s[b] != c)
		b++;
	if (!(a = (char *)malloc(sizeof(char) * (b + 1))))
		return (NULL);
	b = 0;
	while (s[b] && s[b] != c)
	{
		a[b] = s[b];
		b++;
	}
	a[b] = '\0';
	return (a);
}

char			**ft_split(char const *s, char c)
{
	char	**a;
	int		b;
	int		d;

	if (!s || !(a = (char **)malloc(sizeof(char*) * (ft_wordlen(s, c) + 1))))
		return (NULL);
	b = 0;
	d = 0;
	while (s[b])
	{
		while (s[b] && (s[b] == c))
			b++;
		if (s[b] && s[b] != c)
		{
			a[d] = ft_cword(s + b, c);
			d++;
			while (s[b] && s[b] != c)
				b++;
		}
	}
	a[d] = NULL;
	return (a);
}
