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

const t_builtin	g_builtin[] =
{
{"echo", b_echo},
{"cd", b_cd},
{"pwd", b_pwd},
{"export", b_export},
{"unset", b_unset},
{"env", b_env},
{"exit", b_exit},
};

int	b_is_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (i < BUILTIN_NUM)
	{
		if (ft_strcmp(cmd, g_builtin[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}