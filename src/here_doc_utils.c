/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/11 10:39:27 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_here_doc(t_exec_st *exec_st)
{
	int	i;

	i = 0;
	dup2(exec_st->hd_list[exec_st->cmd], STDIN_FILENO);
	while (exec_st->hd_list[i])
	{
		close(exec_st->hd_list[i]);
		i++;
	}
	return (0);
}

static int	here_doc_readline(char *delimiter, int file, t_env *env,
		t_exec_st *exec_st)
{
	char	*buff;

	start_heredoc();
	while (1)
	{
		buff = readline("Input something: ");
		if (!buff && !rl_eof_found)
			return (-1);
		if (rl_eof_found || !ft_strncmp(delimiter, buff, ft_strlen(delimiter)))
			break ;
		buff = parse_env_var(buff, env, exec_st);
		write(file, buff, ft_strlen(buff));
		write(file, "\n", 1);
		free(buff);
	}
	free(buff);
	return (0);
}

void	child_here_doc(char	*delimiter, t_exec_st *exec_st, t_env *env)
{
	int	readline_result;

	readline_result = here_doc_readline(delimiter, exec_st->fd[1], env,
			exec_st);
	free_moi_ca(NULL, exec_st->ope_quotes, exec_st);
	free(exec_st);
	if (readline_result < 0)
		exit(-1);
	exit(0);
}
