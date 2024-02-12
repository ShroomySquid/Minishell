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

int	b_echo(char **args, char **env)
{
	bool	n_flag;
	int		i;

	(void)env;
	n_flag = false;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
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
