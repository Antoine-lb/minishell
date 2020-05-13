/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:15:03 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 10:20:42 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			c;

	if (n == 0 || dst == src)
		return (dst);
	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	c = 0;
	while (n > c)
	{
		a[c] = b[c];
		c++;
	}
	return (dst);
}
