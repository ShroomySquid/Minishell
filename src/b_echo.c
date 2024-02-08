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

	(void)env;
	n_flag = false;
	args++;
	if (args[0] && ft_strcmp(args[0], "-n") == 0)
	{
		n_flag = true;
		args++;
	}
	while (*args)
	{
		ft_printf("%s", *args);
		args++;
		if (*args)
			ft_printf(" ");
	}
	if (!n_flag)
		ft_printf("\n");
	return (0);
}
