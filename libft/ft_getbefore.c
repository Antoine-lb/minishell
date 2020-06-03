/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getbefore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:24:30 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 08:57:31 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getbefore(char *str, int c, int i)
{
	int	a;
	int	b;

	a = i;
	b = 0;
	if ((int)ft_strlen(str) - 1 < a)
		return (-1);
	while ((int)str[a - 1] == c)
	{
		b++;
		a--;
	}
	if (b % 2 == 0)
		return (1);
	return (0);
}
