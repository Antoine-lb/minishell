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
    ft_putstr_fd("error: too many arguments\n", 0);
    return (1);
  }
  else if (len == 2)
  {
    if (chdir(args[1]) == -1)
    {
      ft_putstr_fd("error: Not a directory\n", 0);
      last_exit_code(1);
      return (1);
    }
  }
  else if (len == 1)
  {
    home_path = get_env_var_value("HOME", env);
    if (chdir(home_path) == -1)
    {
      ft_putstr_fd("error: something went wrong\n", 0);
      free(home_path);
      return (1);
    }
    free(home_path);
  }
  return (0);
}