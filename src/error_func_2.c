/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:22:07 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/15 08:52:49 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	error_cmd_not_found(t_exec_st *exec_st, int *return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(exec_st->cmd_args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exec_st->ret = 127;
	*return_value = 1;
}

void	error_no_file(t_exec_st *exec_st, int *return_value, char **cmd_paths)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_paths[exec_st->i], STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	exec_st->ret = 127;
	*return_value = 1;
}

void	error_is_dir(t_exec_st *exec_st, int *return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(exec_st->cmd_args[0], STDERR_FILENO);
	ft_putstr_fd(": is a directory\n", STDERR_FILENO);
	exec_st->ret = 126;
	*return_value = 1;
}

void	error_permission_d(t_exec_st *exec_st,
	int *return_value, char **cmd_paths)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_paths[exec_st->i], STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	exec_st->ret = 126;
	*return_value = 1;
}

int	error_builtin(t_exec_st *exec_st, char ***line_args)
{
	close_here_docs(exec_st);
	close(exec_st->fd[0]);
	close(exec_st->fd[1]);
	free_moi_ca(NULL, *line_args, exec_st);
	return (1);
}
