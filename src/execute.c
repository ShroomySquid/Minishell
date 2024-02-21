/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:33:37 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/12 12:17:59 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *path, char **args, t_env *env, int *ret)
{
	char		**envp;
	t_builtin	builtin;

	if (!path || !args)
		return (-1);
	envp = env_to_tab(env);
	if (!envp)
		return (-1);
	builtin = get_builtin(path);
	if (ft_strcmp(path, builtin.name) == 0)
	{
		*ret = (builtin.func)(args, envp);
		free_all(envp);
		return (*ret);
	}
	*ret = execve(path, args, envp);
	free_all(envp);
	return (*ret);
}
