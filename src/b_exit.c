/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:25:55 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/22 15:26:26 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_exit(char **args, char **env)
{
	(void)env;
	if (!args)
		exit(0);
	if (args[2])
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	else if (args[1] && !ft_isdigit(*(args[1])))
	{
		ft_printf("exit\nminishell: exit: %s: numeric argument required\n",
			args[1]);
		exit(255);
	}
	else if (args[1])
		exit(ft_atoi(args[1]));
	exit(0);
}

void	b_true_exit(char **buff)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_clear_history();
	ft_printf("\n[exit]\n");
	b_exit(buff, NULL);
}
