/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:51:52 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/12 17:15:16 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_count_2d_char(char **arg)
{
  int i;

  i = 0;
  while (arg[i] != NULL)
    i++;
  return (i);
}

int bi_cd(char **args, char ***env)
{
  int len;
  char *home_path;

  len = ft_count_2d_char(args);
  if (len >= 3)
  {
    printf("error: too many arguments\n");
    return (1);
  }
  else if (len == 2)
  {
    if (chdir(args[1]) == -1)
    {
      printf("error: Not a directory\n");
      return (1);
    }
  }
  else if (len == 1)
  {
    home_path = get_env_var_value("HOME", env);
    if (chdir(home_path) == -1)
    {
      printf("error: something went wrong\n");
      free(home_path);
      return (1);
    }
    free(home_path);
  }
  return (0);
}
