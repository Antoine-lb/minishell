/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:15:19 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/16 19:14:31 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	a;
	unsigned int	b;
	size_t			len;

	a = 0;
	b = 0;
	len = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[a] != '\0' && a < dstsize)
		a++;
	while (src[b] != '\0' && a < dstsize - 1)
		dst[a++] = src[b++];
	if (dstsize != 0 && dstsize >= len)
		dst[a] = '\0';
	if (dstsize < ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	return (ft_strlen(src) + len);
}
