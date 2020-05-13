/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:40:42 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 08:36:11 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			c;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	c = -1;
	if (a > b)
		while ((int)(--len) >= 0)
			*(a + len) = *(b + len);
	else
		while (len > ++c)
			*(a + c) = *(b + c);
	return (dst);
}
