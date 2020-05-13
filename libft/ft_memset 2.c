/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:34:38 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 10:19:06 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*a;
	size_t				d;

	if (len == 0)
		return (b);
	a = (unsigned char *)b;
	d = 0;
	while (d < len)
		a[d++] = (unsigned char)c;
	return (b);
}
