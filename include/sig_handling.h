/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:05:09 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/22 03:40:04 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HANDLING_H
# define SIG_HANDLING_H

# include <signal.h>
# include "minishell.h"

typedef struct sigaction	t_sigaction;

# define CTRLC SIGINT
# define CTRLSL SIGQUIT

void	sig_interactive_handler(int signum);
void	be_patient(void);
void	setup_interactive(void);
void	setup_non_interactive(void);
void	start_heredoc(void);
void	signal_fix(t_exec_st *temp_exec, char **temp_args, t_env *temp_env);
void	sig_heredoc_handler(int signum);

#endif
