/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:22:07 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/18 10:37:34 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(s_pipe *pipe, char **line)
{
	if (!pipe->pipes_nbr)
	{
		pipe->i--;
		return ;
	}
	if (pipe->fd[0] >= pipe->min_fd)
	{
		if (pipe->fd[1] != pipe->max_fd)
			pipe->fd[0] -= 2;
		pipe->fd[1] -= 2;
	}
	pipe->child_list[pipe->pipes_nbr - pipe->i] = pipe->child;
	pipe->i--;
	if (pipe->i == 0)
		pipe->child_list[pipe->pipes_nbr - pipe->i] = 0;
	while (ft_strncmp("|", line[pipe->cmd_ptr], 2))
		pipe->cmd_ptr++;
	pipe->cmd_ptr++;
}

void	parent_close(s_pipe *pipe)
{
	if (!pipe->pipes_nbr)
	{
		wait(&pipe->child);
		free(pipe->child_list);
		return ;
	}
	pipe->i++;
	while (pipe->max_fd >= pipe->min_fd)
	{
		close(pipe->max_fd);
		pipe->max_fd--;
	}
	while (pipe->child_list[pipe->i])
	{
		wait(&pipe->child_list[pipe->i]);
		pipe->i++;
	}
	free(pipe->child_list);
}

void	close_child(s_pipe *pipe)
{
	int ite;

	ite = pipe->max_fd;
	if (pipe->i != pipe->pipes_nbr)
	{
		dup2(pipe->fd[0], STDIN_FILENO);
		close(pipe->fd[0]);
	}
	if (pipe->i != 0)
	{
		dup2(pipe->fd[1], STDOUT_FILENO);
		close(pipe->fd[1]);
	}
	while (ite >= pipe->min_fd)
	{
		if (ite != pipe->fd[0] && ite != pipe->fd[1])
			close(ite);
		ite--;
	}
}

void	child_process(s_pipe *pipe, char **line)
{
	int ite;
	
	if (pipe->pipes_nbr)
		close_child(pipe);
	ite = 0;
	while (ft_strncmp("|", line[pipe->cmd_ptr + ite], 2))
		ite++;
	pipe->cmd_args = ft_calloc(ite + 1, sizeof(char *));
	ite = 0;
	while (ft_strncmp("|", line[pipe->cmd_ptr + ite], 2))
	{
		pipe->cmd_args[ite] = ft_strdup(line[pipe->cmd_ptr + ite]);
		ite++;
	}
	pipe->cmd_args[ite] = 0;
}
