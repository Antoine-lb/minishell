/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:09:49 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/16 16:03:39 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	a;

	a = -1;
	while (++a < ft_strlen(s) + 1)
		if (*(s + a) == (char)c)
			return ((char *)(s + a));
	return (NULL);
}

char	*ft_nstrchr(const char *s, char *c)
{
	int	next;

	next = ft_ngetnext((char *)s, 0, c);
	if (next == 0 && !ft_includes(s[0], c))
		return (NULL);
	return ((char *)(s + next));
}
