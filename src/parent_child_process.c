/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:22:07 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/26 12:02:16 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_process(t_exec_st *exec_st, char **line)
{
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
		dup2(exec_st->temp_STDOUT, STDOUT_FILENO);
	//exec_st->i++;
	/*
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
	*/
	while (ft_strncmp("|", line[exec_st->cmd_ptr], 2) && exec_st->i)
		exec_st->cmd_ptr++;
	if (exec_st->i)
		exec_st->cmd_ptr++;
	return (0);
}

void	parent_close(t_exec_st *exec_st)
{
	int i;
	int a;
	/*
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
	*/
	i = 0;
	close(exec_st->fd[0]);
	close(exec_st->fd[1]);
	if (exec_st->pipes_nbr)
		dup2(exec_st->temp_STDIN, STDIN_FILENO);
	while (exec_st->child_list[i])
	{
		ft_printf("Waiting for: %d\n", exec_st->child_list[i]);
		a = waitpid(0, &exec_st->child_list[i], 0);
		ft_printf("Waiting done for: %d, wait returned : %d\n", exec_st->child_list[i], a);
		i++;
	}
	free(exec_st->child_list);
}
/*
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
*/
int	child_process(t_exec_st *exec_st, char **line, char **cmd_paths)
{
	int ite;
	int return_value;
	
	return_value = 0;
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
	if (access(cmd_paths[exec_st->i], X_OK < 0) < 0)
	{
		return_value = 1;
		dup2(exec_st->temp_STDOUT, STDOUT_FILENO);
		ft_printf("Minishell: %s: command not found\n", cmd_paths[exec_st->i]);
	}
	close(exec_st->temp_STDIN);
	close(exec_st->temp_STDOUT);
	return (return_value);
}
