/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_meta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:43:57 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/22 03:36:08 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_handling.h"

void	setup_interactive(void)
{
	t_sigaction	act;
	t_sigaction	ign;

	act = (t_sigaction){0};
	ign = (t_sigaction){0};
	act.sa_handler = sig_interactive_handler;
	act.sa_flags = 0;
	ign.sa_handler = SIG_IGN;
	ign.sa_flags = SA_RESTART;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &ign, NULL);
}

void	setup_non_interactive(void)
{
	t_sigaction	act;

	act = (t_sigaction){0};
	act.sa_handler = SIG_DFL;
	act.sa_flags = 0;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &act, NULL);
}

void	be_patient(void)
{
	t_sigaction	act;

	act = (t_sigaction){0};
	act.sa_handler = SIG_IGN;
	act.sa_flags = SA_RESTART;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &act, NULL);
}

void	start_heredoc(void)
{
	t_sigaction	act;

	act = (t_sigaction){0};
	rl_catch_signals = 1;
	act.sa_handler = sig_heredoc_handler;
	act.sa_flags = 0;
	sigaction(CTRLC, &act, NULL);
}
