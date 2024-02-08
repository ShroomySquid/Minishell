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
					ft_putstr_fd("minishell: cd: ", 2);
					ft_putstr_fd(env[i] + 5, 2);
					ft_putstr_fd(": ", 2);
					ft_putstr_fd(strerror(errno), 2);
					ft_putstr_fd("\n", 2);
					return (1);
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
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else if (errno == ENOTDIR)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": Not a directory\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
		}
		return (1);
	}
	return (0);
}
