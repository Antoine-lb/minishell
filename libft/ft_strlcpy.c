/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:11:54 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/17 09:36:43 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t a;
	size_t b;

	a = 0;
	b = 0;
	while (src[b] != '\0' && b < dstsize - 1 && dstsize > 0)
	{
		dst[b] = src[b];
		b++;
	}
	if (dstsize - b > 0)
		dst[b] = '\0';
	while (src[a])
		a++;
	return (a);
}
