/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/26 12:01:15 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	innit_line(t_exec_st *exec_st)
{
	dup2(exec_st->temp_stdin, STDIN_FILENO);
	dup2(exec_st->temp_stdout, STDOUT_FILENO);
	setup_interactive();
}

int	final_exit(t_exec_st *exec_st, t_env *env)
{
	close(exec_st->temp_stdin);
	close(exec_st->temp_stdout);
	b_true_exit(NULL, exec_st, env, true);
	return (1);
}

int	is_empty_buffer(char *buff)
{
	int	i;

	i = 0;
	while (is_white_space(buff[i]))
		i++;
	if (buff[i])
		return (0);
	free(buff);
	return (1);
}
