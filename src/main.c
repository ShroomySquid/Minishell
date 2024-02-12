/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/12 13:43:01 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell.h"

int	exec_builtin(char **line_args, t_env *env, t_exec_st *exec_st)
{
	exec_st->ret = 0;
	line_args = line_rm_redirection(line_args,
			check_redirection(line_args, exec_st));
	if (!line_args || exec_st->ret)
	{
		free_all(line_args);
		exec_st->ret = 1;
		return (1);
	}
	if (line_args[0] && !ft_strncmp(line_args[0], "exit", 5))
	{
		b_true_exit(line_args, exec_st, env, true);
		return (1);
	}
	else if (is_env_cmd(line_args[0]))
	{
		exec_st->ret = exec_env(line_args[0], line_args, env);
		free_moi_ca(NULL, line_args, exec_st);
		return (1);
	}
	trigger_here_docs(line_args, exec_st, env);
	execute(line_args[0], line_args, env, &exec_st->ret);
	return (0);
}

void	innit_line(t_exec_st *exec_st)
{
	dup2(exec_st->temp_stdin, STDIN_FILENO);
	dup2(exec_st->temp_stdout, STDOUT_FILENO);
	setup_interactive();
}

int	final_exit(t_exec_st *exec_st, t_env *env)
{
	exec_st->ret = 0;
	close(exec_st->temp_stdin);
	close(exec_st->temp_stdout);
	b_true_exit(NULL, exec_st, env, true);
	return (1);
}

int	run_minishell(t_exec_st *exec_st, t_env *env)
{
	char	**line_args;
	char	*buff;

	innit_line(exec_st);
	buff = recieve_input();
	if (!buff)
		return (1);
	line_args = parsing_line(buff, exec_st, env);
	if (!line_args || !line_args[0])
		return (error_parsing(line_args), 0);
	exec_st->pipes_nbr = seek_pipe(line_args, exec_st);
	exec_st->hd_list = ft_calloc(exec_st->nbr_hd + 3, sizeof(int));
	if (!exec_st->hd_list)
		return (error_malloc_hd(exec_st, line_args), 1);
	if (exec_st->pipes_nbr == 0 && b_is_builtin(line_args[0]))
	{
		if (exec_builtin(line_args, env, exec_st) == 1)
			return (0);
	}
	else
		exec_line(exec_st, line_args, env);
	free_moi_ca(NULL, line_args, exec_st);
	return (0);
}

int	main(int argc, char	**argv, char **envp)
{
	t_exec_st	*exec_st;
	t_env		*env;

	if (innit_main(argc, argv, &exec_st))
		return (1);
	env = env_innit(envp);
	while (1)
	{
		if (run_minishell(exec_st, env))
			break ;
	}
	return (final_exit(exec_st, env));
}
