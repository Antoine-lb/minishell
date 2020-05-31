/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 07:04:40 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/19 15:48:14 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*a;
	int		b;

	b = 0;
	if (!s)
		return (NULL);
	if (!f)
		return (ft_strdup(s));
	if (!(a = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[b])
	{
		a[b] = (*f)(b, s[b]);
		b++;
	}
	a[b] = '\0';
	return (a);
}
