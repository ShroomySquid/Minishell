/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:22:07 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/21 09:23:39 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(t_exec_st *exec_st, char **line)
{
	if (!exec_st->pipes_nbr)
	{
		exec_st->i--;
		return ;
	}
	if (exec_st->fd[0] >= exec_st->min_fd)
	{
		if (exec_st->fd[1] != exec_st->max_fd)
			exec_st->fd[0] -= 2;
		exec_st->fd[1] -= 2;
	}
	exec_st->child_list[exec_st->pipes_nbr - exec_st->i] = exec_st->child;
	exec_st->i--;
	if (exec_st->i == 0)
		exec_st->child_list[exec_st->pipes_nbr - exec_st->i] = 0;
	while (ft_strncmp("|", line[exec_st->cmd_ptr], 2))
		exec_st->cmd_ptr++;
	exec_st->cmd_ptr++;
}

void	parent_close(t_exec_st *exec_st)
{
	if (!exec_st->pipes_nbr)
	{
		wait(&exec_st->child);
		free(exec_st->child_list);
		return ;
	}
	exec_st->i++;
	while (exec_st->max_fd >= exec_st->min_fd)
	{
		close(exec_st->max_fd);
		exec_st->max_fd--;
	}
	while (exec_st->child_list[exec_st->i])
	{
		wait(&exec_st->child_list[exec_st->i]);
		exec_st->i++;
	}
	free(exec_st->child_list);
}

void	close_child(t_exec_st *exec_st)
{
	int ite;

	ite = exec_st->max_fd;
	if (exec_st->i != exec_st->pipes_nbr)
	{
		dup2(exec_st->fd[0], STDIN_FILENO);
		close(exec_st->fd[0]);
	}
	if (exec_st->i != 0)
	{
		dup2(exec_st->fd[1], STDOUT_FILENO);
		close(exec_st->fd[1]);
	}
	while (ite >= exec_st->min_fd)
	{
		if (ite != exec_st->fd[0] && ite != exec_st->fd[1])
			close(ite);
		ite--;
	}
}

void	child_process(t_exec_st *exec_st, char **line)
{
	int ite;
	
	if (exec_st->pipes_nbr)
		close_child(exec_st);
	ite = 0;
	while (ft_strncmp("|", line[exec_st->cmd_ptr + ite], 2))
		ite++;
	exec_st->cmd_args = ft_calloc(ite + 1, sizeof(char *));
	ite = 0;
	while (ft_strncmp("|", line[exec_st->cmd_ptr + ite], 2))
	{
		exec_st->cmd_args[ite] = ft_strdup(line[exec_st->cmd_ptr + ite]);
		ite++;
	}
	exec_st->cmd_args[ite] = 0;
}
