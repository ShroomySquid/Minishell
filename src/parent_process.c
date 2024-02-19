/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:22:07 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/11 10:39:29 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	increment_cmd_here_doc(t_exec_st *exec_st, char **line)
{
	int	i;

	i = 0;
	while (line[exec_st->cmd_ptr + i]
		&& ft_strncmp("|", line[exec_st->cmd_ptr + i], 2))
	{
		if (!ft_strncmp("<<", line[exec_st->cmd_ptr + i], 3))
			exec_st->cmd++;
		i++;
	}
}

int	parent_process(t_exec_st *exec_st, char **line)
{
	while (ft_strncmp("|", line[exec_st->cmd_ptr], 2 && exec_st->i))
		exec_st->cmd_ptr++;
	if (exec_st->i)
		exec_st->cmd_ptr++;
	if (exec_st->i)
	{
		dup2(exec_st->fd[0], STDIN_FILENO);
		close(exec_st->fd[0]);
	}
	if (pipe(exec_st->fd))
	{
		ft_printf("Pipe func failed\n");
		return (1);
	}
	if (exec_st->i != exec_st->pipes_nbr)
	{
		dup2(exec_st->fd[1], STDOUT_FILENO);
		close(exec_st->fd[1]);
	}
	else if (exec_st->pipes_nbr)
		dup2(exec_st->temp_stdout, STDOUT_FILENO);
	increment_cmd_here_doc(exec_st, line);
	return (0);
}

void	close_here_docs(t_exec_st *exec_st)
{
	int	i;

	i = 0;
	while (exec_st->hd_list[i])
	{
		close(exec_st->hd_list[i]);
		i++;
	}
}

void	parent_close(t_exec_st *exec_st)
{
	int	i;
	int	stat_loc;

	i = 0;
	close(exec_st->fd[0]);
	close(exec_st->fd[1]);
	if (exec_st->pipes_nbr)
		dup2(exec_st->temp_stdin, STDIN_FILENO);
	be_patient();
	if (exec_st->hd_list[0])
		close_here_docs(exec_st);
	while (exec_st->child_list[i])
	{
		waitpid(exec_st->child_list[i], &stat_loc, 0);
		if (WIFEXITED(stat_loc))
			exec_st->ret = WEXITSTATUS(stat_loc);
		else if (WIFSIGNALED(stat_loc))
			exec_st->ret = WTERMSIG(stat_loc) + 128;
		else if (WIFSTOPPED(stat_loc))
			exec_st->ret = WSTOPSIG(stat_loc) + 128;
		i++;
	}
	setup_interactive();
	free(exec_st->child_list);
}
