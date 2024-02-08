/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:33:37 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/25 11:38:43 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(char *path, char **args, t_env *env, int *ret)
{
	int		i;
	char	**envp;

	i = 0;
	if (!path || !args)
		return (-1);
	envp = env_to_tab(env);
	if (!envp)
		return (-1);
	while (i < BUILTIN_NUM)
	{
		if (ft_strcmp(path, g_builtin[i].name) == 0)
		{
			*ret = (g_builtin[i].func)(args, envp);
			free_all(envp);
			return (*ret);
		}
		i++;
	}
	*ret = execve(path, args, envp);
	ft_printf("execve returned %d\n", *ret);
	free_all(envp);
	return (*ret);
}

void	get_args(t_exec_st *exec_st, char **line)
{
	int	ite;

	ite = 0;
	while (ft_strncmp("|", line[exec_st->cmd_ptr + ite], 2))
		ite++;
	exec_st->cmd_args = ft_calloc(ite + 1, sizeof(char *));
	ite = 0;
	while (ft_strncmp("|", line[exec_st->cmd_ptr + ite], 2))
	{
		exec_st->cmd_args[ite] = ft_strdup(line[exec_st->cmd_ptr + ite]);
		ite++;
	}
	exec_st->cmd_args[ite] = 0;
}
