/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:33:37 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/16 14:33:43 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *path, char **args, char **env)
{
	int		i;

	i = 0;
	if (!path)
		return (-1);
	while (i < BUILTIN_NUM)
	{
		if (ft_strcmp(path, g_builtin[i].name) == 0)
			return ((g_builtin[i].func)(args, env));
		i++;
	}
	return (execve(path, args, env));
}

void	get_args(s_pipe *pipe, char **line)
{
	int ite;

	ite = 0;
	while (ft_strncmp("|", line[pipe->cmd_ptr + ite], 2))
		ite++;
	pipe->cmd_args = ft_calloc(ite + 1, sizeof(char *));
	ite = 0;
	while (ft_strncmp("|", line[pipe->cmd_ptr + ite], 2))
	{
		pipe->cmd_args[ite] = ft_strdup(line[pipe->cmd_ptr + ite]);
		ite++;
	}
	pipe->cmd_args[ite] = 0;
}
