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

typedef struct sigation t_sigaction;

#define CTRLC SIGINT
#define CTRLSL SIGQUIT

#endif
