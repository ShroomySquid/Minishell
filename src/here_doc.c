/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 11:42:17 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *delimiter, t_exec_st *exec_st, t_env *env)
{
	int		child;
	int		status;

	child = fork();
	if (child < 0)
		return (-1);
	if (!child)
		child_here_doc(delimiter, exec_st, env);
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
	return (file);
}

// Ceci est une fonction. Elle fait des choses.
int	trigger_here_docs(char **line_args, t_exec_st *exec_st, t_env *env)
{
	int	i;
	int	file;

	exec_st->cmd = 0;
	i = 0;
	file = 0;
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
