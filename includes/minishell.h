/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:08:19 by ale-baux          #+#    #+#             */
/*   Updated: 2020/02/24 11:49:09 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <libc.h>
#include "../libft/libft.h"
#include "./command.h"


typedef struct	s_command
{
	int cmd;
	char flag;
	char *arg;
	int value_returned;
	t_command *next;
	t_command *prev;
}				t_command

#endif
