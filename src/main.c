/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/08 14:27:03 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell.h"

int	seek_pipe(char	**line_args, t_exec_st *exec_st)
{
	int	i;
	int	pipe_nbr;
	int	last_cmd_hd;

	i = 0;
	pipe_nbr = 0;
	exec_st->nbr_hd = 0;
	last_cmd_hd = -1;
	while (line_args[i])
	{
		if (!ft_strncmp("<<", line_args[i], 3) && last_cmd_hd != pipe_nbr)
		{
			exec_st->nbr_hd++;
			last_cmd_hd = pipe_nbr;
		}
		if (!ft_strncmp("|", line_args[i], 2))
			pipe_nbr++;
		i++;
	}
	return (pipe_nbr);
}

void	free_moi_ca(char **cmd_paths, char **line_args, t_exec_st *exec_st)
{
	if (line_args)
		free_all(line_args);
	if (cmd_paths)
		free_all(cmd_paths);
	if (exec_st->hd_list)
		free(exec_st->hd_list);
	exec_st->hd_list = NULL;
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

char	**parsing_line(char *buff, t_exec_st *exec_st, t_env *env)
{
	char	**temp_line;
	char	*temp_buff;

	temp_buff = parse_operators(buff);
	temp_buff = parse_env_var(temp_buff, env, exec_st);
	temp_line = ft_split_quote(temp_buff);
	remove_quotes(temp_line, exec_st);
	free(temp_buff);
	free(buff);
	return (temp_line);
}

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

int	innit_main(int argc, char **argv, t_exec_st **exec_st)
{
	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	*exec_st = ft_calloc(1, sizeof(t_exec_st));
	if (!*exec_st)
	{
		perror("Malloc failed for exec_st");
		return (1);
	}
	(*exec_st)->temp_stdout = dup(STDOUT_FILENO);
	(*exec_st)->temp_stdin = dup(STDIN_FILENO);
	if (!(*exec_st)->temp_stdin || !(*exec_st)->temp_stdout)
		return (error_dup(*exec_st));
	(*exec_st)->ope_quotes = set_ope_quotes();
	if (verify_ope_quotes((*exec_st)->ope_quotes))
	{
		free(*exec_st);
		return (1);
	}
	return (0);
}

int	main(int argc, char	**argv, char **envp)
{
	char		*buff;
	char		**line_args;
	t_exec_st	*exec_st;
	t_env		*env;

	if (innit_main(argc, argv, &exec_st))
		return (1);
	env = env_innit(envp);
	while (1)
	{
		dup2(exec_st->temp_stdin, STDIN_FILENO);
		dup2(exec_st->temp_stdout, STDOUT_FILENO);
		setup_interactive();
		buff = recieve_input();
		if (!buff)
			break ;
		add_history(buff);
		line_args = parsing_line(buff, exec_st, env);
		if (!line_args || !line_args[0])
		{
			error_parsing(line_args);
			continue ;
		}
		exec_st->pipes_nbr = seek_pipe(line_args, exec_st);
		exec_st->hd_list = ft_calloc(exec_st->nbr_hd + 3, sizeof(int));
		if (!exec_st->hd_list)
			error_malloc_hd(exec_st, line_args);
		if (exec_st->pipes_nbr == 0 && b_is_builtin(line_args[0]))
		{
			if (exec_builtin(line_args, env, exec_st) == 1)
				continue ;
		}
		else
			exec_line(exec_st, line_args, env);
		free_moi_ca(NULL, line_args, exec_st);
	}
	exec_st->ret = 0;
	close(exec_st->temp_stdin);
	close(exec_st->temp_stdout);
	b_true_exit(NULL, exec_st, env, true);
	return (0);
}
