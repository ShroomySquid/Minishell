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
		if (ft_strcmp(args[0], g_builtin[i].name) == 0)
			return ((g_builtin[i].func)(args));
		i++;
	}
	return (execve(path, args, env));
}
