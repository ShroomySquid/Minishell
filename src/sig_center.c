/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:09:24 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/09 15:09:29 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_handling.h"

void	sig_interactive_handler(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
