/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <gsharony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 07:43:22 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/15 08:51:26 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = *lst;
	while (b)
	{
		if (b->next)
			a = b->next;
		else
			a = NULL;
		ft_lstdelone(b, del);
		b = a;
	}
	(*lst) = NULL;
}
