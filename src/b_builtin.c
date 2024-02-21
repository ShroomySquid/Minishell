/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_builtin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:54:34 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/16 14:54:37 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	get_builtin(char *cmd)
{
	int				i;
	const t_builtin	builtins[] = {
	{"echo", b_echo},
	{"cd", b_cd},
	{"pwd", b_pwd},
	{"export", b_export},
	{"unset", b_unset},
	{"env", b_env},
	{"exit", b_exit_mock},
	};

	i = 0;
	while (i < BUILTIN_NUM)
	{
		if (ft_strcmp(cmd, builtins[i].name) == 0)
			return (builtins[i]);
		i++;
	}
	return (builtins[i]);
}

int	b_is_builtin(char *cmd)
{
	t_builtin	builtin;

	builtin = get_builtin(cmd);
	if (ft_strcmp(cmd, builtin.name) == 0)
		return (1);
	return (0);
}
