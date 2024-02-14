/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/14 10:35:09 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minishell.h"

int	seek_pipe(char	**line_args, t_exec_st *exec_st)
{
	int	i;
	int	pipe_nbr;

	i = 0;
	pipe_nbr = 0;
	exec_st->nbr_hd = 0;
	while (line_args[i])
	{
		if (!ft_strncmp("<<", line_args[i], 3))
			exec_st->nbr_hd++;
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

	add_history(buff);
	temp_buff = parse_errors(buff);
	if (temp_buff)
	{
		free(buff);
		error_parsing(temp_buff);
		return (NULL);
	}
	temp_buff = parse_operators(buff);
	temp_buff = parse_env_var(temp_buff, env, exec_st);
	temp_line = ft_split_quote(temp_buff);
	remove_quotes(temp_line, exec_st);
	free(temp_buff);
	temp_buff = parse_errors_again(temp_line);
	free(buff);
	if (!temp_buff)
		return (temp_line);
	free_all(temp_line);
	error_parsing(temp_buff);
	return (NULL);
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
