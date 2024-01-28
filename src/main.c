/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/28 11:52:23 by fbarrett         ###   ########.fr       */
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
	exec_st->nbr_HD = 0;
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


int	run_each_cmd(t_exec_st *exec_st, char **cmd_paths, t_env *env, char **line)
{
	char	**line_args;
	int		line_args_nbr;

	while (exec_st->i <= exec_st->pipes_nbr)
	{
		parent_process(exec_st, line);
		if	((exec_st->child = fork()) < 0)
			return (1);
		if (!exec_st->child)
		{
			if (child_process(exec_st, line, cmd_paths))
			{
				free_all(exec_st->cmd_args);
				exit (1);
			}
			line_args_nbr = check_redirection(exec_st->cmd_args, exec_st);
			if (line_args_nbr >= 0)
			{
				line_args = line_rm_redirection(exec_st->cmd_args, line_args_nbr);
				if (!line_args || execute(cmd_paths[exec_st->i],
						line_args, env) == -1)
					perror("Cmd failed to execute");
				if (line_args)
					free_all(line_args);
			}
			free_all(exec_st->cmd_args);
			exit (1);
		}
		else
		{
			exec_st->child_list[exec_st->i] = exec_st->child;
			exec_st->i++;
		}
	}
	return (0);
}

int	run_cmds(char **line, char	**cmd_paths, t_env *env, t_exec_st *exec_st)
{
	exec_st->i = 0;
	exec_st->cmd_ptr = 0;
	exec_st->child_list = ft_calloc(exec_st->pipes_nbr + 2, sizeof(char *));
	if (!exec_st->child_list)
	{
		perror("Malloc failed for exec_st->child_list");
		return (1);
	}
	exec_st->child_list[exec_st->pipes_nbr + 1] = 0;
	if (run_each_cmd(exec_st, cmd_paths, env, line))
	{
		parent_close(exec_st);
		return (1);
	}
	parent_close(exec_st);
	return (0);
}

void	free_moi_ca(char *buff, char **cmd_paths, char **line_args, t_exec_st *exec_st)
{
	if (line_args)
		free_all(line_args);
	if (cmd_paths)
		free_all(cmd_paths);
	if (buff)
		free(buff);
	if (exec_st->HD_list)
		free(exec_st->HD_list);
}

int	exec_line(t_exec_st *exec_st, char **line_args, t_env *env, char *buff)
{
	char	**cmd_paths;

	trigger_here_docs(line_args, exec_st);
	cmd_paths = ft_calloc((exec_st->pipes_nbr) + 2, sizeof(char *));
	if (!cmd_paths)
	{
		perror("Malloc failed for: cmd_paths");	
		free_moi_ca(buff, cmd_paths, line_args, exec_st);
		return (1);
	}
	seek_all_cmds(&cmd_paths, line_args, env);
	run_cmds(line_args, cmd_paths, env, exec_st);
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
	t_env	*env;

	(void)argc;
	(void)argv;
	sig_innit();
	env = env_innit(envp);
	exec_st = ft_calloc(1, sizeof(t_exec_st));
	if (!exec_st)
	{
		perror("Malloc failed for exec_st");
		return (1);
	}
	exec_st->temp_STDOUT = dup(STDOUT_FILENO);
	exec_st->temp_STDIN = dup(STDIN_FILENO);
	if (!exec_st->temp_STDIN || !exec_st->temp_STDOUT)
	{
		perror("dup failed");
		free(exec_st);
		return (1);
	}
	//printf("stdin: %d stdout: %d\n", exec_st->temp_STDIN, exec_st->temp_STDOUT); 
	while (exec_st)
	{
		buff = recieve_input();
		if (!buff)
			break ;
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
		exec_st->HD_list = ft_calloc(exec_st->nbr_HD + 3, sizeof(int));
		if (!exec_st->HD_list)
		{
			perror("Malloc failed for HD_list");
			free_all(line_args);
			free(exec_st);
			return (1);
		}
		if (exec_st->pipes_nbr == 0 && b_is_builtin(line_args[0]))
		{
			if (line_args[0] && !ft_strncmp(line_args[0], "exit", 5))
			{
				free(buff);
				b_true_exit(line_args);
			}
			else if (is_env_cmd(line_args[0]))
			{
				exec_env(line_args[0], line_args, env);
				free_moi_ca(buff, NULL, line_args, exec_st);
				continue ;
			}
			trigger_here_docs(line_args, exec_st);
			execute(line_args[0], line_args, env);
			free_moi_ca(buff, NULL, line_args, exec_st);
		}
		else
			exec_line(exec_st, line_args, env, buff);
		//unlink_here_doc();
	}
	close(exec_st->temp_STDIN);
	close(exec_st->temp_STDOUT);
	free(exec_st);
	b_true_exit(NULL);
	return (0);
}
