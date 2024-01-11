/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:05:09 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/09 15:05:25 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLING_H
#define SIG_HANDLING_H

#include <signal.h>
#include "minishell.h"
#include <termios.h>

typedef struct sigaction t_sigaction;

#define CTRLC SIGINT
#define CTRLSL SIGQUIT

void	sig_interactive_handler(int signum);
int		sig_access(int signum);
void	sig_ignore(int signum);
void	setup_terminal(void);
void	setup_interactive(void);
void	sig_innit(void);

#endif
