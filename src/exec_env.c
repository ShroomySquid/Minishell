/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:12:56 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/26 18:14:09 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_cmd(char *path)
{
	return (!strcmp(path, "export") || !strcmp(path, "unset"));
}

int	exec_env(char *path, char **args, t_env *envp)
{
	if (!strcmp(path, "export"))
		return (b_parent_export(args, envp));
	else if (!strcmp(path, "unset"))
		return (b_parent_unset(args, envp));
	return (0);
}