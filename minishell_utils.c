/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:37:41 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/09 14:15:38 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **possible_paths, char *cmd)
{
	int		i;
	char	*path;
	char	*valid_path;

	i = 0;
	while (possible_paths[i])
	{
		path = ft_strjoin(possible_paths[i], "/");
		valid_path = ft_strjoin(path, cmd);
		free(path);
		if (valid_path && !access(valid_path, X_OK))
			return (valid_path);
		free(valid_path);
		i++;
	}
	return (NULL);
}

char	*seek_cmd(char *cmd, char **envp)
{
	int		i;
	char	**possible_paths;
	char	*valid_path;

	i = 0;
	if (ft_strchr(cmd, 47))
		return (cmd);
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	possible_paths = ft_split(envp[i] + 5, ':');
	if (!possible_paths)
		return (0);
	valid_path = find_path(possible_paths, cmd);
	free_all(possible_paths);
	return (valid_path);
}
/*
void	close_moi_ca(t_ints ints)
{
	if (ints.fdin != 0)
		close(ints.fdin);
	if (ints.fdout != 1)
		close(ints.fdout);
	close(ints.fd[0]);
	close(ints.fd[1]);
}

int	dup_moi_ca(t_ints ints, int argc)
{
	if (ints.start == 0)
	{
		dup2(ints.fdin, STDIN_FILENO);
		close(ints.fd[0]);
	}
	if (ints.i == (argc - 2))
	{
		dup2(ints.fdout, STDOUT_FILENO);
		close(ints.fd[1]);
	}
	else
		dup2(ints.fd[1], STDOUT_FILENO);
	return (0);
}
*/
char	*cut_path(char *path)
{
	int	i;
	char *path_buffer;

	i = 0;
	while (path[i] && path[i] != 47)
		i++;
	path_buffer = ft_strdup(path);
	return (ft_substr(path_buffer, i, 1000));
}
