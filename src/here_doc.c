/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/12 13:28:36 by fbarrett         ###   ########.fr       */
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

int	here_doc(char	*delimiter, t_exec_st *exec_st, t_env *env)
{
	int		readline_result;
	int		child;
	int		status;

	child = fork();
	if (child < 0)
		return (-1);
	if (!child)
	{
		readline_result = here_doc_readline(delimiter, exec_st->fd[1], env,
				exec_st);
		free_moi_ca(NULL, NULL, exec_st);
		free_all(exec_st->ope_quotes);
		free(exec_st);
		if (readline_result < 0)
			exit(-1);
		exit(0);
	}
	be_patient();
	waitpid(child, &status, 0);
	setup_interactive();
	close(exec_st->fd[1]);
	if (WIFSIGNALED(status))
	{
		exec_st->ret = WTERMSIG(status);
		ft_printf("\n");
		return (1);
	}
	return (0);
}

void	finish_here_doc(t_exec_st *exec_st)
{
	exec_st->cmd++;
	exec_st->hd_list[exec_st->cmd] = 0;
	exec_st->cmd = -1;
}

int	here_doc_input(t_exec_st *exec_st, char **line_args, int i, t_env *env)
{
	int	file;

	if (exec_st->hd_list[exec_st->cmd])
		close(exec_st->hd_list[exec_st->cmd]);
	if (pipe(exec_st->fd) < 0)
		return (-1);
	file = here_doc(line_args[i + 1], exec_st, env);
	if (file)
		return (file);
	exec_st->hd_list[exec_st->cmd] = exec_st->fd[0];
	exec_st->hd_bool = 1;
	return (file);
}

// Ceci est une fonction. Elle fait des choses.
int	trigger_here_docs(char **line_args, t_exec_st *exec_st, t_env *env)
{
	int	i;
	int	file;

	exec_st->cmd = 0;
	i = 0;
	while (line_args[i] && line_args[i + 1])
	{
		if (!ft_strncmp("<<", line_args[i], 3))
		{
			file = here_doc_input(exec_st, line_args, i, env);
			exec_st->cmd++;
			if (file)
				return (1);
		}
		i++;
	}
	finish_here_doc(exec_st);
	return (file);
}
