/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/10 15:02:40 by fbarrett         ###   ########.fr       */
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
	ft_printf("There is %d pipes\n", pipe_nbr);
	return (pipe_nbr);
}

int	run_single(char	**line, char	*cmd_path,	char	**envp)
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
			perror("Execve failed to execute");	
	}
	free(cmd_path);
	free_all(line);
	exit (1);
}

void	seek_all_cmds(char **cmd_paths, char **line_args, char **envp)
{
	int i;
	int args;

	args = 0;
	i = 0;
	while (line_args[i])
	{
		if (i == 0 || !ft_strncmp("|", line_args[i - 1], 2))
		{
			cmd_paths[args] = seek_cmd(line_args[0], envp);
			args++;
		}
		i++;
	}
	cmd_paths[args] = 0;
}

int main(int argc, char	**argv, char **envp)
{
	char	*buff;
	char	**line_args;
	int		pipes_nbr;
	char	**cmd_paths;
	int		i;
	int		fd[2];

	i = 0;
	if (envp)
		argc += 0;
	else
		printf("%s\n", argv[0]);
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
		pipes_nbr = seek_pipe(line_args);
		if (pipes_nbr < 1)
		{
			cmd_paths = ft_calloc(1, sizeof(char *));
			cmd_paths[0] = seek_cmd(line_args[0], envp);
			cmd_paths[1] = 0;
		}
		else
		{
			cmd_paths = ft_calloc(1 + pipes_nbr, sizeof(char *));
			seek_all_cmds(cmd_paths, line_args, envp);
		}
		i = -1;
		while (i < pipes_nbr)
		{
			i++;
			if (!cmd_paths[i])
			{
				free_all(line_args);
				free_all(cmd_paths);
				free(buff);				
				continue ;
			}
		}
		/*
		i = 0;
		while (i < pipes_nbr)
		{
			pipe(fd);
			printf("%d, %d, \n", fd[0], fd[1]);
			i++;
		}
		*/
		if (!pipes_nbr)
			run_single(line_args, cmd_paths[0], envp);
		free_all(line_args);
		free_all(cmd_paths);
		free(buff);
	}
	clear_history();
	return (0);
}

