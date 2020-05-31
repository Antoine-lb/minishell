/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:36:10 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 11:31:38 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			t;

	if (n == 0 || dst == src)
		return (dst);
	t = 0;
	a = (unsigned char*)dst;
	b = (unsigned char*)src;
	while (t < n)
	{
		a[t] = b[t];
		if (b[t] == (unsigned char)c)
			return (a + t + 1);
		t++;
	}
	return (NULL);
}
