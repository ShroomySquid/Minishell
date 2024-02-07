/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/07 09:46:36 by fbarrett         ###   ########.fr       */
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

void	free_moi_ca(char **cmd_paths, char **line_args, t_exec_st *exec_st)
{
	if (line_args)
		free_all(line_args);
	if (cmd_paths)
		free_all(cmd_paths);
	if (exec_st->HD_list)
		free(exec_st->HD_list);
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

char **parsing_line(char *buff, t_exec_st *exec_st, t_env *env)
{
	char** temp_line;
	char* temp_buff;

	temp_buff = parse_operators(buff);
	temp_buff = parse_env_var(temp_buff, env);
	printf("temp_buff: %s\n", temp_buff);
	temp_line = ft_split_quote(temp_buff);
	remove_quotes(temp_line, exec_st);
	print_array(temp_line);
	free (buff);
	return (temp_line);
}

int exec_builtin(char **line_args, t_env *env, t_exec_st *exec_st)
{
	if (line_args[0] && !ft_strncmp(line_args[0], "exit", 5))
		b_true_exit(line_args, exec_st, env);
	else if (is_env_cmd(line_args[0]))
	{
		exec_env(line_args[0], line_args, env);
		free_moi_ca(NULL, line_args, exec_st);
		return (1);
	}
	trigger_here_docs(line_args, exec_st, env);
	execute(line_args[0], line_args, env);
	free_moi_ca(NULL, line_args, exec_st);
	return (0);
}

int innit_main(int argc, char **argv, t_exec_st **exec_st)
{
	(void)argc;
	(void)argv;
	sig_innit();
	*exec_st = ft_calloc(1, sizeof(t_exec_st));
	if (!*exec_st)
	{
		perror("Malloc failed for exec_st");
		return (1);
	}
	(*exec_st)->temp_STDOUT = dup(STDOUT_FILENO);
	(*exec_st)->temp_STDIN = dup(STDIN_FILENO);
	ft_printf("fds : %d %d\n", (*exec_st)->temp_STDIN, (*exec_st)->temp_STDOUT);
	if (!(*exec_st)->temp_STDIN || !(*exec_st)->temp_STDOUT)
		return(error_dup(*exec_st));
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
	char	*buff;
	char	**line_args;
	t_exec_st	*exec_st;
	t_env	*env;

	if (innit_main(argc, argv, &exec_st))
		return (1);
	env = env_innit(envp);
	while (1)
	{
		setup_interactive();
		buff = recieve_input();
		setup_non_interactive();
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
		exec_st->HD_list = ft_calloc(exec_st->nbr_HD + 3, sizeof(int));
		if (!exec_st->HD_list)
			error_malloc_HD(exec_st, line_args);
		if (exec_st->pipes_nbr == 0 && b_is_builtin(line_args[0]))
		{
			if (exec_builtin(line_args, env, exec_st) == 1)
				continue ;
		}
		else
			exec_line(exec_st, line_args, env);
		free_moi_ca(NULL, line_args, exec_st);
	}
	close(exec_st->temp_STDIN);
	close(exec_st->temp_STDOUT);
	free_all(exec_st->ope_quotes);
	free(exec_st);
	b_true_exit(NULL, NULL, env);
	return (0);
}
