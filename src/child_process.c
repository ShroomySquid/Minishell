/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:22:07 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/21 15:26:56 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

int	innit_child_process(t_exec_st *exec_st, char **line)
{
	int	ite;

	ite = 0;
	while (ft_strncmp("|", line[exec_st->cmd_ptr + ite], 2))
		ite++;
	exec_st->cmd_args = ft_calloc(ite + 1, sizeof(char *));
	if (!exec_st->cmd_args)
		return (-1);
	ite = 0;
	while (ft_strncmp("|", line[exec_st->cmd_ptr + ite], 2))
	{
		exec_st->cmd_args[ite] = ft_strdup(line[exec_st->cmd_ptr + ite]);
		ite++;
	}
	return (check_redirection(exec_st->cmd_args, exec_st));
}

void	check_error(t_exec_st *exec_st,
	int *return_value, char **cmd_paths, struct stat *buf)
{
	if (b_is_builtin(exec_st->cmd_args[0]))
		return_value = 0;
	else if (!ft_strchr(cmd_paths[exec_st->i], '/'))
		error_cmd_not_found(exec_st, return_value);
	else if (stat(cmd_paths[exec_st->i], buf) < 0)
		error_no_file(exec_st, return_value, cmd_paths);
	else if (S_ISDIR(buf->st_mode))
		error_is_dir(exec_st, return_value);
	else if (!(buf->st_mode & S_IXUSR))
		error_permission_d(exec_st, return_value, cmd_paths);
}

void	close_child(t_exec_st *exec_st)
{
	int	i;

	if (exec_st->i == exec_st->pipes_nbr)
		close(exec_st->fd[1]);
	close(exec_st->fd[0]);
	close(exec_st->temp_stdin);
	close(exec_st->temp_stdout);
	i = 0;
	while (exec_st->hd_list[i])
	{
		close(exec_st->hd_list[i]);
		i++;
	}
}

int	child_process(t_exec_st *exec_st, char **line, char **cmd_paths)
{
	int			new_malloc;
	int			return_value;
	struct stat	buf;

	return_value = 0;
	new_malloc = innit_child_process(exec_st, line);
	if (new_malloc >= 0)
	{
		exec_st->cmd_args = line_rm_redirection(exec_st->cmd_args, new_malloc);
		free(cmd_paths[exec_st->i]);
		cmd_paths[exec_st->i] = seek_cmd(exec_st->cmd_args[0], exec_st->env);
		fix_quotes(&exec_st->cmd_args, exec_st);
	}
	else
	{
		close_child(exec_st);
		return (1);
	}
	check_error(exec_st, &return_value, cmd_paths, &buf);
	close_child(exec_st);
	return (return_value);
}
