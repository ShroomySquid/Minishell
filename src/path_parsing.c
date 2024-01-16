/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:37:41 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/16 14:34:34 by fbarrett         ###   ########.fr       */
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
	ft_printf("Command not found: %s\n", cmd);	
	return (NULL);
}

char	*seek_cmd(char *cmd, char **envp)
{
	int		i;
	char	**possible_paths;
	char	*valid_path;

	i = 0;
	if (ft_strchr(cmd, 47))
	{
		if (!access(cmd, X_OK))
		{
			ft_printf("valid cmd: %s\n", cmd);
			return (ft_strdup(cmd));
		}
		ft_printf("Command not found: %s\n", cmd);
		return (NULL);	
	}
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	possible_paths = ft_split(envp[i] + 5, ':');
	if (!possible_paths)
		return (0);
	valid_path = find_path(possible_paths, cmd);
	free_all(possible_paths);
	return (valid_path);
}

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

void    seek_all_cmds(char ***cmd_paths, char **line_args, char **envp)
{
	int i;
	int args;
	
	args = 1;
	i = 1;
	(*cmd_paths)[0] = seek_cmd(line_args[0], envp);
	while (line_args[i] && (*cmd_paths)[0])
	{
		if (!ft_strncmp("|", line_args[i - 1], 2))
		{
			(*cmd_paths)[args] = seek_cmd(line_args[i], envp);
			args++;
			if (!(*cmd_paths)[args - 1])
				break ;
		}
		i++;
	}
	(*cmd_paths)[args] = 0;
}
