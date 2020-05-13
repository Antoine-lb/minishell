/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:03:27 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/19 06:06:17 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_len(int nbr)
{
	int		a;
	long	b;

	a = 0;
	b = (long)nbr;
	if (nbr < 0)
	{
		b = -b;
		a++;
	}
	while (b)
	{
		b /= 10;
		a++;
	}
	return (a);
}

static	void	ft_strrev(char *str, int nbr)
{
	int		a;
	int		b;
	char	c;

	a = 0;
	b = 0;
	if (nbr < 0)
		a++;
	while (str[b])
		b++;
	b -= 1;
	while (a < b)
	{
		c = str[a];
		str[a] = str[b];
		str[b] = c;
		a++;
		b--;
	}
}

static	void	ft_fill(long nb, int a, char *s)
{
	char	c;

	while (nb > 0)
	{
		c = ((nb % 10) + '0');
		s[a] = c;
		nb /= 10;
		a++;
	}
	s[a] = '\0';
}

char			*ft_itoa(int n)
{
	int		a;
	long	nb;
	char	*s;

	a = 0;
	nb = (long)n;
	if (n == 0)
	{
		if (!(s = (char*)malloc(sizeof(char) * 2)))
			return (NULL);
		s[0] = '0';
		s[1] = '\0';
		return (s);
	}
	if (!(s = (char *)malloc(sizeof(char) * ft_len(n) + 1)))
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		s[a] = '-';
		a++;
	}
	ft_fill(nb, a, s);
	ft_strrev(s, n);
	return (s);
}
