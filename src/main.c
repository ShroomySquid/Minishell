/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/15 12:13:20 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	seek_pipe(char	**line_args)
{
	int i;
	int pipe_nbr;

	i = 0;
	pipe_nbr = 0;
	while (line_args[i])
	{
		if (!ft_strncmp("|", line_args[i], 2))
			pipe_nbr++;
		i++;
	}
	return (pipe_nbr);
}

int	run_single_cmd(char	**line, char *cmd_path,	char **envp, s_pipe *pipe)
{
	if	((pipe->child = fork()) < 0)
		return (1);
	if (pipe->child > 0)
	{
		waitpid(pipe->child, &pipe->error, 0);
		return (0);
	}
	if (!pipe->child)
	{
		if (execve(cmd_path, line, envp) == -1)
			perror("execve failed to execute");	
	}
	//free(cmd_path);
	exit (1);
	//return (1);
}

void	parent_process(s_pipe *pipe, char **line)
{
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

int	run_each_cmd(s_pipe *pipes, char **cmd_paths, char **envp, char **line)
{
	while (pipes->i >= 0)
	{
		if	((pipes->child = fork()) < 0)
			return (1);
		if (pipes->child > 0)
		{
			parent_process(pipes, line);
			continue ;
		}
		if (!pipes->child)
		{
			child_process(pipes, line);
			if (execve(cmd_paths[pipes->pipes_nbr - pipes->i], pipes->cmd_args, envp) == -1)
				perror("execve failed to execute");	
		}
		free_all(pipes->cmd_args);
		exit (1);
	}
	return (0);
}

int	run_cmds_pipe(char **line, char	**cmd_paths, char **envp, s_pipe *pipes)
{
	pipes->i = 0;
	pipes->cmd_ptr = 0;
	pipes->child_list = ft_calloc(pipes->pipes_nbr + 2, sizeof(int));
	while (pipes->i < pipes->pipes_nbr)
	{
		pipe(pipes->fd);
		if (pipes->i == 0)
			pipes->min_fd = pipes->fd[0];
		pipes->i++;	
	}
	pipes->max_fd = pipes->fd[1];
	if (run_each_cmd(pipes, cmd_paths, envp, line))
	{
		parent_close(pipes);
		return (1);
	}
	parent_close(pipes);
	return (0);
}

int	check_cmds(s_pipe *pipe, char **cmd_paths)
{
	pipe->i = 0;
	while (pipe->i < (pipe->pipes_nbr + 1))
	{
		if (!cmd_paths[pipe->i])
			break ;
		pipe->i++;
	}
	if (pipe->i <= pipe->pipes_nbr)
		return (1);
	return (0);
}

void	free_moi_ca(char *buff, char **cmd_paths, char **line_args)
{
	free_all(line_args);
	free_all(cmd_paths);
	free(buff);
}

int	exec_line(s_pipe *pipe, char **line_args, char **envp, char *buff)
{
	char	**cmd_paths;

	pipe->pipes_nbr = seek_pipe(line_args);
	if (pipe->pipes_nbr == 0)
	{
		cmd_paths = ft_calloc(2, sizeof(char *));
		cmd_paths[0] = seek_cmd(line_args[0], envp);
		cmd_paths[1] = 0;
		if (cmd_paths[0])
			run_single_cmd(line_args, cmd_paths[0], envp, pipe);
	}
	else
	{
		cmd_paths = ft_calloc(2 + pipe->pipes_nbr, sizeof(char *));
		seek_all_cmds(&cmd_paths, line_args, envp);
		if (!check_cmds(pipe, cmd_paths))
			run_cmds_pipe(line_args, cmd_paths, envp, pipe);
	}
	free_moi_ca(buff, cmd_paths, line_args);
	return (0);
}

int main(int argc, char	**argv, char **envp)
{
	char	*buff;
	char	**line_args;
	s_pipe	*pipe;

	(void)argc;
	(void)argv;
	pipe = ft_calloc(1, sizeof(char *));
	while (1)
	{
		buff = readline("> ");
		add_history(buff);
		if (!buff)
		{
			printf("Somehow readline failed to save on buff");
			break ;
		}
		if (!ft_strncmp("exit", buff, 4))
		{
			free(buff);
			break ;
		}
		line_args = ft_split_quote(buff, ' ');
		if (!line_args[0])
		{
			free(line_args);
			free(buff);
			continue ;
		}
		exec_line(pipe, line_args, envp, buff);
	}
	free(pipe);
	// y faut rl_clear_history
	clear_history();
	return (0);
}
