/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/06 10:34:15 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_each_cmd(t_exec_st *exec_st, char **cmd_paths, t_env *env, char **line)
{
	char	**line_args;
	int		line_args_nbr;

	while (exec_st->i <= exec_st->pipes_nbr)
	{
		setup_interactive();
		parent_process(exec_st, line);
		exec_st->child = fork();
		if	(exec_st->child < 0)
			return (1);
		if (!exec_st->child)
		{
			setup_non_interactive();
			exec_st->ret = 0;
			if (child_process(exec_st, line, cmd_paths))
			{
				free_all(exec_st->cmd_args);
				free_all(cmd_paths);
				free_all(line);
				free(exec_st->child_list);
				exec_st->ret = 127;
				b_true_exit(NULL, exec_st, env, false);
			}
			line_args_nbr = check_redirection(exec_st->cmd_args, exec_st);
			if (line_args_nbr >= 0)
			{
				line_args = line_rm_redirection(exec_st->cmd_args, line_args_nbr);
				fix_quotes(&line_args, exec_st);
				if (!line_args || execute(cmd_paths[exec_st->i],
										  line_args, env, &exec_st->ret) == -1)
					perror("Cmd failed to execute");
				if (line_args)
					free_all(line_args);
			}
			free_all(exec_st->cmd_args);
			free_all(cmd_paths);
			free_all(line);
			free(exec_st->child_list);
			b_true_exit(NULL, exec_st, env, false);
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
	exec_st->child_list = ft_calloc(exec_st->pipes_nbr + 2, sizeof(int));
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

int	exec_line(t_exec_st *exec_st, char **line_args, t_env *env)
{
	char	**cmd_paths;

	trigger_here_docs(line_args, exec_st);
	cmd_paths = ft_calloc((exec_st->pipes_nbr) + 2, sizeof(char *));
	if (!cmd_paths)
	{
		perror("Malloc failed for: cmd_paths");	
		free_all(cmd_paths);
		return (1);
	}
	seek_all_cmds(&cmd_paths, line_args, env);
	run_cmds(line_args, cmd_paths, env, exec_st);
	free_all(cmd_paths);
	return (0);
}
