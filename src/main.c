/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/10 11:41:56 by fbarrett         ###   ########.fr       */
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

int main(int argc, char	**argv, char **envp)
{
	char	*buff;
	char	**line_args;
	int		pipes_nbr;
	char	*cmd_path;
	int		i;
	int		fd[2];

	i = 0;
	if (envp)
		argc += 0;
	else
		printf("%s\n", argv[0]);
	while (1)
	{
		ft_printf("> ");
		buff = get_next_line(0);
		if (!buff)
		{
			printf("get_next_line failed to saved on buffer");
			return (1);
		}
		i = ft_strlen(buff) - 1;
		buff[i] = '\0';
		if (!ft_strncmp("exit", buff, 4))
		{
			free(buff);
			break ;
		}
		line_args = ft_split_quote(buff, ' ');
		pipes_nbr = seek_pipe(line_args);
		cmd_path = seek_cmd(line_args[0], envp);
		i = 0;
		while (i < pipes_nbr)
		{
			pipe(fd);
			printf("%d, %d, \n", fd[0], fd[1]);
			i++;
		}
		if (!cmd_path)
		{
			write(1, "No matching commands\n", 21);
			continue ;
		}
		else if (!pipes_nbr)
			run_single(line_args, cmd_path, envp);
		free_all(line_args);
		free(cmd_path);
		free(buff);
	}
	return (0);
}
