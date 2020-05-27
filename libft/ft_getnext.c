/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <gsharony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 07:43:22 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/15 08:51:26 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getnext(char *str, int from, char c)
{
	while (str[from])
	{
		if (str[from] == c)
			return (from);
		from++;
	}
	return (from);
}

int		ft_ngetnext(char *str, int from, char *c)
{
	int	a;
	int	b;
	int	t;

	a = 0;
	b = 0;
	t = 0;
	while (c[a])
	{
		t = ft_getnext(str, from, c[a]);
		if (a == 0 || t < b)
			b = t;
		a++;
	}
	return (b);
}
