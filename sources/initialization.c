/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_in_and_out.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guysharon <guysharon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 09:13:35 by guysharon         #+#    #+#             */
/*   Updated: 2020/03/30 12:13:17 by guysharon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/command.h"

void	init_cursor(char **tmp, t_cursor *csr)
{
	(*csr).a = -1;
	(*csr).b = -1;
	(*csr).c = 0;
	(*tmp) = NULL;
}

void	init_parser(t_parser *psr)
{
	(*psr).sep = -1;
	(*psr).command = NULL;
}
