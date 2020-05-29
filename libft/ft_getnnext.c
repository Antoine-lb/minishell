/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnnext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <gsharony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 07:43:22 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/15 08:51:26 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getnnext(char *str, int from, char c)
{
	while (str[from])
	{
		if (str[from] != c)
			return (from);
		from++;
	}
	return (from);
}

int		ft_ngetnnext(char *str, int from, const char *c)
{
	int	a;
	int	b;

	a = from;
	while (a < (int)ft_strlen(str))
	{
		b = 0;
		while (c[b] && (int)c[b] != (int)str[a])
		{
			b++;
		}
		if ((int)ft_strlen(c) == b)
			return (a);
		a++;
	}
	return (a);
}
