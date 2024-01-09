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

//Handle SIGINT and SIGQUIT

int	sig_access(int signum)
{
	static int	sig = 0;
	int			ret;

	ret = sig;
	sig = signum;
	return (ret);
}

void	sig_interactive_handler(int signum)
{
	sig_access(signum);
	if (signum == CTRLC)
		ft_printf("\n");
}

