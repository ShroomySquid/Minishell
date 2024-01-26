/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:25:55 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/26 10:51:31 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_exit(char **args, char **env)
{
	(void)env;
	(void)args;
	exit(0);
}

void	b_true_exit(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_clear_history();
	ft_printf("\n[exit]\n");
	exit(0);
}
