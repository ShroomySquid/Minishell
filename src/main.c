/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/22 13:13:32 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	seek_pipe(char	**line_args, t_exec_st *exec_st)
{
	int i;
	int pipe_nbr;
	int last_cmd_HD;

	i = 0;
	pipe_nbr = 0;
	exec_st->nbr_HD = -1;
	last_cmd_HD = -1;
	while (line_args[i])
	{
		if (!ft_strncmp("<<", line_args[i], 3) && last_cmd_HD != pipe_nbr)
		{
			exec_st->nbr_HD++;
			last_cmd_HD = pipe_nbr;
		}
		if (!ft_strncmp("|", line_args[i], 2))
			pipe_nbr++;
		i++;
	}
	return (pipe_nbr);
}


int	run_each_cmd(t_exec_st *exec_st, char **cmd_paths, char **envp, char **line)
{
	char	**line_args;
	int		line_args_nbr;

	while (exec_st->i >= 0)
	{
		if	((exec_st->child = fork()) < 0)
			return (1);
		if (exec_st->child > 0)
		{
			parent_process(exec_st, line);
			continue ;
		}
		if (!exec_st->child)
		{
			child_process(exec_st, line);
			line_args_nbr = check_redirection(exec_st->cmd_args, exec_st);
			if (line_args_nbr < 0)
				return (1);
			line_args = line_rm_redirection(exec_st->cmd_args, line_args_nbr);
			if (execute(cmd_paths[exec_st->pipes_nbr - exec_st->i],
					line_args, envp) == -1)
				perror("execve failed to execute");
		}
		free_all(exec_st->cmd_args);
		exit (1);
	}
	return (0);
}

int	run_cmds(char **line, char	**cmd_paths, char **envp, t_exec_st *exec_st)
{
	exec_st->i = 0;
	exec_st->cmd_ptr = 0;
	exec_st->child_list = ft_calloc(exec_st->pipes_nbr + 2, sizeof(char *));
	while (exec_st->i < exec_st->pipes_nbr)
	{
		pipe(exec_st->fd);
		if (exec_st->i == 0)
			exec_st->min_fd = exec_st->fd[0];
		exec_st->i++;	
	}
	exec_st->max_fd = exec_st->fd[1];
	if (run_each_cmd(exec_st, cmd_paths, envp, line))
	{
		parent_close(exec_st);
		return (1);
	}
	parent_close(exec_st);
	return (0);
}

int	check_cmds(t_exec_st *exec_st, char **cmd_paths)
{
	exec_st->i = 0;
	while (exec_st->i < (exec_st->pipes_nbr + 1))
	{
		if (!cmd_paths[exec_st->i])
			break ;
		exec_st->i++;
	}
	if (exec_st->i <= exec_st->pipes_nbr)
		return (1);
	return (0);
}

void	free_moi_ca(char *buff, char **cmd_paths, char **line_args, t_exec_st *exec_st)
{
	free_all(line_args);
	free_all(cmd_paths);
	free(buff);
	free_all(exec_st->HD_list);
}

int	exec_line(t_exec_st *exec_st, char **line_args, char **envp, char *buff)
{
	char	**cmd_paths;

	//exec_st->pipes_nbr = seek_pipe(line_args, exec_st);
	//exec_st->HD_list = ft_calloc(exec_st->nbr_HD + 2, sizeof(char *));
	trigger_here_docs(line_args, exec_st);
	exec_st->nbr_HD = 0;
	cmd_paths = ft_calloc((exec_st->pipes_nbr) + 2, sizeof(char *));
	seek_all_cmds(&cmd_paths, line_args, envp);
	if (!check_cmds(exec_st, cmd_paths))
		run_cmds(line_args, cmd_paths, envp, exec_st);
	free_moi_ca(buff, cmd_paths, line_args, exec_st);
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
	t_exec_st	*exec_st;

	(void)argc;
	(void)argv;
	sig_innit();
	exec_st = ft_calloc(1, sizeof(t_exec_st));
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
			free(exec_st);
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
		exec_st->pipes_nbr = seek_pipe(line_args, exec_st);
		exec_st->HD_list = ft_calloc(exec_st->nbr_HD + 3, sizeof(char *));
		exec_line(exec_st, line_args, envp, buff);
		unlink_here_doc();
	}
	return (0);
}
