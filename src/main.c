/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/17 14:29:24 by fbarrett         ###   ########.fr       */
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


int	run_each_cmd(s_pipe *pipes, char **cmd_paths, char **envp, char **line)
{
	char	**line_args;
	int		line_args_nbr;

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
			line_args_nbr = check_redirection(pipes->cmd_args);
			if (line_args_nbr < 0)
				return (1);
			line_args = line_rm_redirection(pipes->cmd_args, line_args_nbr);
			if (execute(cmd_paths[pipes->pipes_nbr - pipes->i],
					pipes->cmd_args, envp) == -1)
				perror("execve failed to execute");
		}
		free_all(pipes->cmd_args);
		exit (1);
	}
	return (0);
}

int	run_cmds(char **line, char	**cmd_paths, char **envp, s_pipe *pipes)
{
	pipes->i = 0;
	pipes->cmd_ptr = 0;
	pipes->child_list = ft_calloc(pipes->pipes_nbr + 2, sizeof(unsigned long int));
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

	cmd_paths = ft_calloc(2 + pipe->pipes_nbr, sizeof(unsigned long int));
	seek_all_cmds(&cmd_paths, line_args, envp);
	if (!check_cmds(pipe, cmd_paths))
		run_cmds(line_args, cmd_paths, envp, pipe);
	free_moi_ca(buff, cmd_paths, line_args);
	return (0);
}

char	*recieve_input(void)
{
	char	*buff;
	char	*temp;
	char	*prompt;

	temp = b_get_pwd_short(NULL);
	if (!temp)
		prompt = ft_strdup("minishell$ ");
	else
	{
		prompt = ft_strjoin(temp, " $ ");
		free(temp);
	}
	buff = readline(prompt);
	free(prompt);
	return (buff);
}

int	main(int argc, char	**argv, char **envp)
{
	char	*buff;
	char	**line_args;
	s_pipe	*pipe;

	(void)argc;
	(void)argv;
	sig_innit();
	pipe = ft_calloc(1, sizeof(s_pipe *));
	while (1)
	{
		buff = recieve_input();
		if (!buff && errno)
		{
			printf("Failed to read line\n");
			break ;
		}
		if (!buff || !ft_strncmp("exit", buff, 5))
		{
			if (buff)
				free(buff);
			free(pipe);
			b_exit(NULL);
			break ;
		}
		add_history(buff);
		line_args = ft_split_quote(buff, ' ');
		if (!line_args || !line_args[0])
		{
			free(buff);
			if (line_args)
				free(line_args);
			else
				ft_printf("Failed to parse line\n");
			continue ;
		}
		exec_line(pipe, line_args, envp, buff);
		unlink_here_doc();
	}
	return (0);
}
