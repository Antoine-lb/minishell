/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:24:30 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 08:57:31 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int		ft_atoi(const char *str)
{
	int				a;
	int				c;
	long long int	d;

	a = 0;
	c = 0;
	d = 0;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-')
	{
		c = 1;
		a++;
	}
	else if (str[a] == '+')
		a++;
	while (str[a] >= 48 && str[a] <= 57)
	{
		d *= 10;
		d += str[a] - 48;
		a++;
	}
	if (c == 1)
		return (-d);
	return (d);
}

int					ft_isnumber(const char *str)
{
	int a;
	int	c;

	a = 0;
	c = 0;
	while (str[a] == ' ' || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-')
	{
		c = 1;
		a++;
	}
	else if (str[a] == '+')
		a++;
	while (str[a])
	{
		if (str[a] >= 48 && str[a] <= 57)
			a++;
		else
			return (0);
	}
	if (c == 1)
		return (-1);
	return (1);
}
