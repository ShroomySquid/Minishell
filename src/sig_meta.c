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

void	setup_interactive(void)
{
	t_sigaction act;
	t_sigaction ign;

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
	t_sigaction act;

	act = (t_sigaction){0};
	act.sa_handler = SIG_DFL;
	act.sa_flags = 0;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &act, NULL);
}

void	be_patient(void)
{
	t_sigaction act;

	act = (t_sigaction){0};
	act.sa_handler = sig_while_waiting;
	act.sa_flags = SA_RESTART;
	sigaction(CTRLC, &act, NULL);
	sigaction(CTRLSL, &act, NULL);
}