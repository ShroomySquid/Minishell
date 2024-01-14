/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/14 13:30:22 by fbarrett         ###   ########.fr       */
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

int	run_single_cmd(char	**line, char	*cmd_path,	char	**envp)
{
	int	child;

	if	((child = fork()) < 0)
		return (1);
	if (child > 0)
	{
		wait(&child);
		return (0);
	}
	if (!child)
	{
		if (execve(cmd_path, line, envp) == -1)
			perror("execve failed to execute");	
	}
	free(cmd_path);
	free_all(line);
	exit (1);
}

void	parent_process(s_pipe *pipe, char **line)
{
	if (pipe->fd[0] >= pipe->min_fd)
	{
		if (pipe->fd[1] != pipe->max_fd)
			pipe->fd[0] -= 2;
		pipe->fd[1] -= 2;
	}
	pipe->i--;
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
	wait(&pipe->child);
}

void	child_process(s_pipe *pipe, char **line)
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

int	run_cmds_pipe(char **line, char	**cmd_paths, char **envp, s_pipe *pipes)
{
	pipes->i = 0;
	pipes->cmd_ptr = 0;
	while (pipes->i < pipes->pipes_nbr)
	{
		pipe(pipes->fd);
		if (pipes->i == 0)
			pipes->min_fd = pipes->fd[0];
		pipes->i++;	
	}
	pipes->max_fd = pipes->fd[1];
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
		free(cmd_paths);
		free_all(pipes->cmd_args);
		free_all(line);
		exit (1);
	}
	parent_close(pipes);
	return (0);
}

void	seek_all_cmds(char ***cmd_paths, char **line_args, char **envp)
{
	int i;
	int args;

	args = 1;
	i = 1;
	(*cmd_paths)[0] = seek_cmd(line_args[0], envp);
	while (line_args[i] && (*cmd_paths)[0])
	{
		if (!ft_strncmp("|", line_args[i - 1], 2))
		{
			(*cmd_paths)[args] = seek_cmd(line_args[i], envp);
			args++;
			if (!(*cmd_paths)[args - 1])
				break ;
		}
		i++;
	}
	(*cmd_paths)[args] = 0;
}

int main(int argc, char	**argv, char **envp)
{
	char	*buff;
	char	**line_args;
	char	**cmd_paths;
	s_pipe	*pipe;

	(void)argc;
	(void)argv;
	(void)envp;
//	setup_interactive();
//	setup_terminal();
	pipe = ft_calloc(1, sizeof(char *));
	while (1)
	{
		buff = readline("> ");
		add_history(buff);
		if (!buff)
		{
			printf("whobolo");
			return (1);
		}
		if (!ft_strncmp("exit", buff, 4))
		{
			free(buff);
			break ;
		}
		line_args = ft_split_quote(buff, ' ');
		pipe->pipes_nbr = seek_pipe(line_args);
		if (pipe->pipes_nbr < 1)
		{
			cmd_paths = ft_calloc(2, sizeof(char *));
			cmd_paths[0] = seek_cmd(line_args[0], envp);
			cmd_paths[1] = 0;
		}
		else
		{
			cmd_paths = ft_calloc(2 + pipe->pipes_nbr, sizeof(char *));
			seek_all_cmds(&cmd_paths, line_args, envp);
		}
		pipe->i = 0;
		while (pipe->i < pipe->pipes_nbr + 1)
		{
			if (!cmd_paths[pipe->i])
			{
				free_all(line_args);
				free_all(cmd_paths);
				free(buff);
				break ;
			}
			pipe->i++;
		}
		if (pipe->i <= pipe->pipes_nbr)
			continue ;
		if (!pipe->pipes_nbr)
		{
			run_single_cmd(line_args, cmd_paths[0], envp);
		}
		else
		{
			run_cmds_pipe(line_args, cmd_paths, envp, pipe);
		}
		free_all(line_args);
		free_all(cmd_paths);
		free(buff);
	}
	// y faut rl_clear_history
	clear_history();
	return (0);
}

