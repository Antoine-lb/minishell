/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsharony <gsharony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:12:40 by gsharony          #+#    #+#             */
/*   Updated: 2019/10/18 11:11:55 by gsharony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*a;
	t_list	*b;

	a = ft_lstnew(f(lst->content));
	b = a;
	while (lst->next)
	{
		lst = lst->next;
		if (!(a->next = ft_lstnew(f(lst->content))))
		{
			ft_lstdelone(a->next, del);
			return (NULL);
		}
		a = a->next;
	}
	return (b);
}
