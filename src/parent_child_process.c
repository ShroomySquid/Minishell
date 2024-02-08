/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:22:07 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/06 15:31:03 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	increment_cmd_here_doc(t_exec_st *exec_st, char **line)
{
	int	i;

	i = 0;
	while (ft_strncmp("|", line[exec_st->cmd_ptr + i], 2))
	{
		i++;
		if (ft_strncmp("<<", line[exec_st->cmd_ptr + i], 3))
		{
			exec_st->cmd++;
			break ;
		}
	}
}

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
		dup2(exec_st->temp_stdout, STDOUT_FILENO);
	while (ft_strncmp("|", line[exec_st->cmd_ptr], 2) && exec_st->i)
		exec_st->cmd_ptr++;
	if (exec_st->i)
	{
		exec_st->cmd_ptr++;
		increment_cmd_here_doc(exec_st, line);
	}
	return (0);
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

int	failed_cmd_msg(t_exec_st *exec_st, char **cmd_paths)
{
	dup2(exec_st->temp_stdout, STDOUT_FILENO);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_paths[exec_st->i], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (1);
}

int	child_process(t_exec_st *exec_st, char **line, char **cmd_paths)
{
	int	ite;
	int	return_value;
	struct stat	buf;

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
	if (b_is_builtin(exec_st->cmd_args[0]))
		return_value = 0;
	else if (!ft_strchr(cmd_paths[exec_st->i], '/'))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec_st->cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exec_st->ret = 127;
		return_value = 1;
	}
	else if (stat(cmd_paths[exec_st->i], &buf) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_paths[exec_st->i], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exec_st->ret = 127;
		return_value = 1;
	}
	else if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(exec_st->cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		exec_st->ret = 126;
		return_value = 1;
//		return (1);
	}
	else if (!(buf.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_paths[exec_st->i], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		exec_st->ret = 126;
		return_value = 1;
//		return (1);
	}
//	if (access(cmd_paths[exec_st->i], X_OK < 0) < 0
//		&& !b_is_builtin(cmd_paths[exec_st->i]))
//		return_value = failed_cmd_msg(exec_st, cmd_paths);
	if (exec_st->i == exec_st->pipes_nbr)
		close(exec_st->fd[1]);
	close(exec_st->fd[0]);
	close(exec_st->temp_stdin);
	close(exec_st->temp_stdout);
	return (return_value);
}
