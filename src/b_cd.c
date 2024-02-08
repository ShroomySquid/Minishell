/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:24:51 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/16 14:26:25 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_cd(char **args, char **env)
{
	int	err;
	int	i;

	(void)env;
	if (!args)
		return (1);
	if (!args[1])
	{
		i = 0;
		while (env[i])
		{
			if (ft_strncmp(env[i], "HOME=", 5) == 0)
			{
				err = chdir(env[i] + 5);
				if (err == -1)
				{
					ft_printf("minishell: cd: %s: %s\n", env[i] + 5,
						strerror(errno));
				}
				return (0);
			}
			i++;
		}
		return (0);
	}
	err = chdir(args[1]);
	if (err == -1)
	{
		if (errno == EACCES)
		{
			ft_printf("minishell: cd: %s: Permission denied\n", args[1]);
		}
		else if (errno == ENOENT)
		{
			ft_printf("minishell: cd: %s: No such file or directory\n",
				args[1]);
		}
		else if (errno == ENOTDIR)
		{
			ft_printf("minishell: cd: %s: Not a directory\n", args[1]);
		}
		else
		{
			ft_printf("minishell: cd: %s: %s\n", args[1], strerror(errno));
		}
	}
	return (0);
}
