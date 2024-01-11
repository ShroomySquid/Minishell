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
#include <termios.h>

//Handle SIGINT and SIGQUIT

void	mask_control_chars(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO | ICANON);
//	term.c_lflag &= ~(ICANON);
//	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &term);
}

void	setup_sigs(void)
{
	t_sigaction act;
	t_sigaction ign;

	act.sa_handler = sig_interactive_handler;
	ign.sa_handler = sig_ignore;
	ign.sa_flags = SA_RESTART;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &ign, NULL);
}

int	sig_access(int signum)
{
	static int	sig = 0;
	int			ret;

	ret = sig;
	sig = signum;
	return (ret);
}

void sig_ignore(int signum)
{
	(void)signum;
}

void	sig_interactive_handler(int signum)
{
	sig_access(signum);
	if (signum == CTRLC)
		ft_printf("\n");
}

