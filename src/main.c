/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/16 15:46:17 by fbarrett         ###   ########.fr       */
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

int	here_doc(int file, char	*delimiter, int *a)
{
	char	*buff;
	char	*here_doc_name;

	here_doc_name = ft_calloc(3, sizeof(char));
	here_doc_name[0] = '.';
	here_doc_name[1] = 'A';
	here_doc_name[2] = '\0';
	if (!access(here_doc_name, F_OK))
		here_doc_name[1] += 1;
	file = open(here_doc_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return (file);
	while (1)
	{
		buff = readline("Input something: ");
		if (!buff)
			return (-1);
		if (!ft_strncmp(delimiter, buff, ft_strlen(delimiter)))
			break ;
		write(file, buff, ft_strlen(buff));
		write(file, "\n", 1);
		free(buff);
	}
	if (buff)
		free(buff);
	close(file);
	file = open(here_doc_name, O_RDONLY, 0000644);
	close(STDIN_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	a += 2;
	free(here_doc_name);
	return (file);
}

int	r_redirect(int file, char *given_file, int *a)
{
	file = open(given_file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return (file);
	close(STDOUT_FILENO);
	dup2(file, STDOUT_FILENO);
	close(file);
	a += 2;
   return (file);	
}

int	ra_redirect(int file, char *given_file, int *a)
{
	file = open(given_file, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (file < 0)
		return (file);
	close(STDOUT_FILENO);
	dup2(file, STDOUT_FILENO);
	close(file);
	a += 2;
   return (file);	
}

int	l_redirect(int file, char *given_file, int *a)
{
	file = open(given_file, O_RDONLY, 0000644);
	if (file < 0)
		return (file);
	close(STDIN_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	a += 2;
   return (file);	
}


int	check_redirection(char **line)
{
	int i;
	int	file;
	int a;

	i = 0;
	a = 0;
	while (line[i])
	{
		if (!ft_strncmp(">", line[i], 2))
		{
			file = r_redirect(file, line[i + 1], &a);
		}
		else if (!ft_strncmp(">>", line[i], 3))
		{
			file = ra_redirect(file, line[i + 1], &a);
		}
		else if (!ft_strncmp("<", line[i], 2))
		{
			file = l_redirect(file, line[i + 1], &a);
		}
		else if (!ft_strncmp("<<", line[i], 3))
		{
			file = here_doc(file, line[i + 1], &a);
		}
		if (file < 0)
		{
			perror("Error");
			return (-1);
		}
		i++;
	}
	return (i - a);
}

char	**line_args_parse(char **line, int args_nbr)
{
	char	**line_args;
	int i;
	int a;

	i = 0;
	a = 0;
	line_args = ft_calloc(args_nbr + 1, sizeof(char *));
	while (line[i])
	{
		if (!ft_strncmp("<", line[i], 2) || !ft_strncmp("<<", line[i], 3) || !ft_strncmp(">", line[i], 2) || !ft_strncmp(">>", line[i], 3))
		{
			i += 2;
			a += 2;
			continue ;
		}
		line_args[i - a] = ft_strdup(line[i]);
		i++;
	}
	line_args[i + a] = 0;
	return (line_args);
}

int	run_single_cmd(char	**line, char *cmd_path,	char **envp, s_pipe *pipe)
{
	char	**line_args;
	int		line_args_nbr;
	
	if	((pipe->child = fork()) < 0)
		return (1);
	if (pipe->child > 0)
	{
		waitpid(pipe->child, &pipe->error, 0);
		return (0);
	}
	if (!pipe->child)
	{
		line_args_nbr = check_redirection(line);
		if (line_args_nbr < 0)
			return (1);
		line_args = line_args_parse(line, line_args_nbr);
		if (execve(cmd_path, line_args, envp) == -1)
			perror("execve failed to execute");
		free(line_args);
	}
	exit (1);
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
			line_args_nbr = check_redirection(line);
			if (line_args_nbr < 0)
				return (1);
			line_args = line_args_parse(pipes->cmd_args, line_args_nbr);
			if (execve(cmd_paths[pipes->pipes_nbr - pipes->i], line_args, envp) == -1)
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

void	unlink_here_doc(void)
{
	char	*here_doc;

	here_doc = ft_calloc(3, sizeof(char));
	here_doc[0] = '.';
	here_doc[1] = 'A';
	here_doc[2] = '\0';
	while (!access(here_doc, F_OK))
	{
		unlink(here_doc);
		here_doc[1]++;
	}
	free(here_doc);
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
		unlink_here_doc();
	}
	free(pipe);
	// y faut rl_clear_history
	clear_history();
	return (0);
}
