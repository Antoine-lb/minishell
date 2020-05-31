/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:03:44 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/16 16:13:57 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	while (a < n - 1 && s1[a] && s1[a] == s2[a])
		a++;
	if (n)
		return (*((unsigned char *)s1 + a) - *((unsigned char *)s2 + a));
	return (0);
}
