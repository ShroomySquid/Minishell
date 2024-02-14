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

static char	*get_home_dir(char	**env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

int	b_cd(char **args, char **env)
{
	char	*home_dir;

	(void)env;
	if (!args)
		return (1);
	if (!args[1])
	{
		home_dir = get_home_dir(env);
		if (!home_dir)
			home_dir = "/";
		if (chdir(home_dir) != -1)
			return (0);
		perror("minishell: cd");
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
