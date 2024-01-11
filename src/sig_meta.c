/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:43:57 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/10 22:43:57 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_handling.h"

void	mask_control_chars(void)
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

	act.sa_handler = sig_interactive_handler;
	ign.sa_handler = sig_ignore;
	ign.sa_flags = SA_RESTART;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &ign, NULL);
}

