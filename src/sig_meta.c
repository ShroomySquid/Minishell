/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:43:57 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/28 11:10:37 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_handling.h"

void	sig_innit(void)
{
//	setup_terminal();
	rl_catch_signals = 0;
	setup_interactive();
}

void	setup_terminal(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO | ICANON);
//	term.c_lflag &= ~(ICANON);
//	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &term);
}

void	setup_interactive(void)
{
	t_sigaction act;
	t_sigaction ign;

	act = (t_sigaction){0};
	ign = (t_sigaction){0};
	act.sa_handler = sig_interactive_handler;
	act.sa_flags = 0;
//	act.sa_flags = SA_INTERRUPT;
//	This flag is necessary on Ubuntu machine else the read() is not interrupted
	ign.sa_handler = sig_ignore;
	ign.sa_flags = SA_RESTART;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &ign, NULL);
}

void	setup_non_interactive(void)
{
	t_sigaction act;

	act = (t_sigaction){0};
	act.sa_handler = SIG_IGN;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &act, NULL);
}