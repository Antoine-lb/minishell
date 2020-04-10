/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_from_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-baux <ale-baux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:44:56 by ale-baux          #+#    #+#             */
/*   Updated: 2020/03/09 17:42:07 by ale-baux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_all_splited_paths(char **splited_paths)
{
	int i;

	i = 0;
	while (splited_paths[i])
	{
		free(splited_paths[i]);
		i++;
	}
	free(splited_paths);
}

char *file_exists(char *cmd, char *path)
{
	char *tmp;
	char *tmp_2;
	int fd;

	tmp = ft_strjoin(path, "/");
	tmp_2 = ft_strjoin(tmp, cmd);
	fd = open(tmp_2, O_RDONLY, 0666);
	free(tmp);
	if (fd != -1)
	{
		close(fd);
		return (tmp_2);
	}
	close(fd);
	free(tmp_2);
	return (NULL);
}

char *get_path_from_env(char *cmd)
{
	int i;
	char *all_paths;
	char **splited_paths;
	char *ret;

	i = 0;
	if (!cmd || cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	all_paths = get_env_var_value("PATH", NULL);
	if (all_paths == NULL)
		return (NULL);
	splited_paths = ft_split(all_paths, ':');
	while (splited_paths[i])
	{
		ret = file_exists(cmd, splited_paths[i]);
		if (ret != NULL)
			return (ret);
		i++;
	}
	free(all_paths);
	free_all_splited_paths(splited_paths);
	return (NULL);
}
