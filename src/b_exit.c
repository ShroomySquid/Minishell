/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:25:55 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/16 14:26:02 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//empty b_exit function
int	b_exit(char **args)
{
	(void)args;
	rl_replace_line("", 0);
	rl_clear_history();
	ft_printf("\n[exit]\n");
	exit(0);
}