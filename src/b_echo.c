/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:24:30 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/16 14:26:21 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static int	is_n_flag(const char *arg)
{
	int	i;

	i = 2;
	if (!arg)
		return (0);
	if (arg[0] == '-' && arg[1] == 'n')
		while (arg[i] == 'n')
			i++;
	else
		return (0);
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	b_echo(char **args, char **env)
{
	bool	n_flag;
	int		i;

	(void)env;
	n_flag = false;
	i = 1;
	while (is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		i++;
		if (args[i])
			ft_printf(" ");
	}
	if (!n_flag)
		ft_printf("\n");
	return (0);
}
