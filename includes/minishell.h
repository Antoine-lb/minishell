/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:08:19 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/09 15:47:04 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <libc.h>
#include "../libft/libft.h"
#include "./command.h"
#include <signal.h>



char *get_path_from_env(char *cmd);


#endif
