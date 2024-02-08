/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:37:41 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/28 11:39:49 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **possible_paths, char *cmd)
{
	int		i;
	char	*path;
	char	*valid_path;

	i = 0;
	if (b_is_builtin(cmd))
		return (ft_strdup(cmd));
	while (possible_paths[i])
	{
		path = ft_strjoin(possible_paths[i], "/");
		valid_path = ft_strjoin(path, cmd);
		if (path)
			free(path);
		if (valid_path && !access(valid_path, X_OK))
			return (valid_path);
		if (valid_path)
			free(valid_path);
		i++;
	}
	return (ft_strdup(cmd));
}

char	*seek_cmd(char *cmd, t_env *env)
{
	int		i;
	char	**possible_paths;
	char	*valid_path;

	i = 0;
	if (!cmd)
		return (0);
	if (cmd[0] == '~' && cmd[1] == '/')
		return (ft_strjoin(env_find(env, "HOME")->value, cmd + 1));
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	env = env_find(env, "PATH");
	possible_paths = ft_split(env->value + 5, ':');
	if (!possible_paths)
		return (0);
	valid_path = find_path(possible_paths, cmd);
	free_all(possible_paths);
	return (valid_path);
}

char	*cut_path(char *path)
{
	int		i;
	char	*path_buffer;

	i = 0;
	while (path[i] && path[i] != 47)
		i++;
	path_buffer = ft_strdup(path);
	return (ft_substr(path_buffer, i, 1000));
}

void	seek_all_cmds(char ***cmd_paths, char **line_args, t_env *env)
{
	int	i;
	int	args;

	args = 1;
	i = 1;
	(*cmd_paths)[0] = seek_cmd(line_args[0], env);
	while (line_args[i] && (*cmd_paths)[0])
	{
		if (!ft_strncmp("|", line_args[i - 1], 2))
		{
			(*cmd_paths)[args] = seek_cmd(line_args[i], env);
			args++;
			if (!(*cmd_paths)[args - 1])
				break ;
		}
		i++;
	}
	(*cmd_paths)[args] = 0;
}
