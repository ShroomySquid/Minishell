/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:09:24 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/22 03:41:36 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_handling.h"

void	signal_fix(t_exec_st *temp_exec, char **temp_args, t_env *temp_env)
{
	int					i;
	static t_exec_st	*exec_st = NULL;
	static char			**args = NULL;
	static t_env		*env = NULL;

	if (temp_exec)
	{
		exec_st = temp_exec;
		args = temp_args;
		env = temp_env;
		return ;
	}
	i = 0;
	while (i < exec_st->cmd)
		close(exec_st->hd_list[i++]);
	close(exec_st->fd[0]);
	close(exec_st->fd[1]);
	close(exec_st->temp_stdout);
	close(exec_st->temp_stdin);
	free_moi_ca(NULL, exec_st->ope_quotes, exec_st);
	free(exec_st);
	env_clear(&env);
	free_all(args);
}

void	sig_heredoc_handler(int signum)
{
	(void) signum;
	signal_fix(NULL, NULL, NULL);
	exit(255);
}

void	sig_interactive_handler(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
