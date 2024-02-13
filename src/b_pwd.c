/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:42:02 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/15 15:42:07 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(char **args, char **env)
{
	char	*pwd;

	(void)args;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory\n", 2);
		return (-1);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}

char	*b_get_pwd_short(char **args)
{
	char	*pwd;
	char	*home;
	char	*short_pwd;

	(void)args;
	pwd = getcwd(NULL, 0);
	home = getenv("HOME");
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory\n", 2);
		return (0);
	}
	if (!home)
	{
		free(pwd);
		return (0);
	}
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
	{
		short_pwd = ft_strjoin("~", pwd + ft_strlen(home));
		free(pwd);
		return (short_pwd);
	}
	return (pwd);
}

int	get_pwd(char *temp_buff, int *a)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	while (pwd[i])
	{
		temp_buff[*a] = pwd[i];
		i++;
		*a += 1;
	}
	free(pwd);
	return (i);
}
