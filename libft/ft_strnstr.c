/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:17:53 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/11 19:06:58 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t a;

	if (*needle == '\0')
		return ((char*)haystack);
	a = ft_strlen(needle);
	while (*haystack != '\0' && len-- >= a)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, a) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
