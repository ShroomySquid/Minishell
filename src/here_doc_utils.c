/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/23 13:42:26 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	close_fd_hd_child(t_exec_st *exec_st)
{
	int	i;

	i = 0;
	while (i < exec_st->cmd)
	{
		close(exec_st->hd_list[i]);
		i++;
	}
	close(exec_st->fd[1]);
	close(exec_st->fd[0]);
	close(exec_st->temp_stdout);
	close(exec_st->temp_stdin);
}

void	child_here_doc(char	*delimiter, t_exec_st *exec_st, t_env *env,
		char **args)
{
	int	readline_result;

	signal_fix(exec_st, args, env);
	readline_result = here_doc_readline(delimiter, exec_st->fd[1], env,
			exec_st);
	close_fd_hd_child(exec_st);
	free_moi_ca(NULL, exec_st->ope_quotes, exec_st);
	free(exec_st);
	env_clear(&env);
	free_all(args);
	if (readline_result < 0)
		exit(-1);
	exit(0);
}
