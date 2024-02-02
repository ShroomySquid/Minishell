/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/02 11:39:53 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *make_pipe_quote_s()
{
	char *str;
	str = malloc(sizeof(char) * 4);
	if (!str)
		return (NULL);
	str[0] = 39;
	str[1] = 124;
	str[2] = 39;
	str[3] = 0;
	return (str);
}

char *make_pipe_quote_d()
{
	char *str;
	str = malloc(sizeof(char) * 4);
	if (!str)
		return (NULL);
	str[0] = 34;
	str[1] = 124;
	str[2] = 34;
	str[3] = 0;
	return (str);
}

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

void fix_quotes(char ***line)
{
	int i;
	char *pipe_s;
	char *pipe_d;

	i = 0;
	if (!line[0])
		return ;
	pipe_s = make_pipe_quote_s();
	pipe_d = make_pipe_quote_d();
	while (line[0][i])
	{
		if (!ft_strncmp(line[0][i], pipe_s, 4) || !ft_strncmp(line[0][i], pipe_d, 4))
		{
			free(line[0][i]);
			line[0][i] = ft_calloc(2, sizeof(char));
			if (!line[0][i])
				break ;
			line[0][i][0] = '|';
			line[0][i][1] = '\0';
		}
		i++;
	}
	free(pipe_s);
	free(pipe_d);
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
				fix_quotes(&line_args);
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
	if (exec_st->ope_quotes)
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

void to_end_quote_length(char quote, char *buff, int *i, int *a)
{
	*i += 1;
	*a += 1;
	while (buff[*i] && buff[*i] != quote)
	{
		*i += 1;
		*a += 1;
	}
}

void to_end_quote(char quote, char *buff, char *temp_buff, int *i, int *a)
{
	temp_buff[*i + *a] = buff[*i];
	*i += 1;
	while (buff[*i] && buff[*i] != quote)
	{
		temp_buff[*i + *a] = buff[*i];
		*i += 1;
	}
	if (buff[*i])
	{	
		temp_buff[*i + *a] = buff[*i];
		*i += 1;
	}
}

int tb_length(char *buff)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (buff[i])
	{
		if (buff[i] == 34 || 39 == buff[i])
			to_end_quote_length(buff[i], buff, &i, &a);
		if (buff[i] && (buff[i] == '<' || buff[i] == '>' || buff[i] == '|'))
		{
			if (buff[i - 1] && buff[i -1] != ' ')
				a++;
			if (buff[i + 1] && buff[i + 1] != ' ')
				a++;
			if (buff[i] == '<' && buff[i + 1] && buff[i + 1] == '<')
			{
				if (buff[i + 2] && buff[i + 2] != ' ')
					a++;
			}
			if (buff[i] == '<' && buff[i + 1] && buff[i + 1] == '<')
			{
				if (buff[i + 2] && buff[i + 2] != ' ')
					a++;
			}
		}
		i++;
		a++;
	}
	a++;
	return (a);
}

char *parse_operators(char *buff)
{
	char *temp_buff;
	int i;
	int a;
	
	temp_buff = ft_calloc(tb_length(buff), sizeof(char));
	if (!temp_buff)
		return (NULL);
	i = 0;
	a = 0;
	while (buff[i])
	{
		if (buff[i] == 34 || 39 == buff[i])
			to_end_quote(buff[i], buff, temp_buff, &i, &a);
		if (buff[i] == '<' || buff[i] == '>' || buff[i] == '|')
		{
			if (buff[i - 1] && buff[i - 1] != ' ' && buff[i - 1] != buff[i])
			{
				temp_buff[i + a] = ' ';
				a++;	
			}
			temp_buff[i + a] = buff[i];
			if ((buff[i] == '<' || buff[i] == '>') && buff[i + 1] && buff[i + 1] == buff[i])
			{
				i++;
				temp_buff[i + a] = buff[i];
			}
			if (buff[i + 1] && buff[i + 1] != ' ')
			{
				a++;
				temp_buff[i + a] = ' ';
			}
		}
		else
			temp_buff[i + a] = buff[i];
		i++;
	}
	return (temp_buff);
}

int new_length(char *arg, int i, int a)
{
	int quote;

	while (arg[i])
	{
		if (arg[i] == 39 || arg[i] == 34)
		{
			quote = arg[i];
			i++;
			while (arg[i] != quote)
			{
				i++;
				a++;
			}
			if (arg[i])
				i++;
		}
		else
		{
			i++;
			a++;
		}
	}
	return (a);
}

char *remove_quote_arg(char *arg)
{
	char *new_arg;
	int quote;
	int a;
	int i;

	i = 0;
	a = 0;
	new_arg = ft_calloc((new_length(arg, i, a) + 1), sizeof(char));
	if (!new_arg)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == 39 || arg[i] == 34)
		{
			quote = arg[i];
			i++;
			while (arg[i] && arg[i] != quote)
			{
				new_arg[a] = arg[i];
				i++;
				a++;
			}
			if (arg[i] == quote)
				i++;
		}
		else if (arg[i])
		{
			new_arg[a] = arg[i];
			i++;
			a++;
		}	
	}
	new_arg[a] = 0;
	free(arg);
	return (new_arg);	
}

int remove_quotes(char **temp_line)
{
	int i;
	char *pipe_d;
	char *pipe_s;

	i = 0;
	pipe_d = make_pipe_quote_d();
	if (!pipe_d)
		return (1);
	pipe_s = make_pipe_quote_s();
	if (!pipe_s)
	{
		free(pipe_d);
		return (1);	
	}
	while(temp_line[i])
	{
		if (!ft_strncmp(pipe_s, temp_line[i], 4) || !ft_strncmp(pipe_d, temp_line[i], 4))
		{
			i++;
			continue ;
		}
		if (ft_strchr(temp_line[i], 34) || ft_strchr(temp_line[i], 39))
		{
			temp_line[i] = remove_quote_arg(temp_line[i]);
			if (!temp_line[i])
			{
				free(pipe_d);
				free(pipe_s);
				return (1);
			}
		}
		i++;
	}
	free(pipe_d);
	free(pipe_s);
	return (0);
}

char **parsing_line(char *buff)
{
	char** temp_line;
	char* temp_buff;

	temp_buff = parse_operators(buff);
	temp_line = ft_split_quote(temp_buff, ' ');
	remove_quotes(temp_line);
	return (temp_line);
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
	exec_st->ope_quotes = set_ope_quotes();
	if (verify_ope_quotes(exec_st->ope_quotes))
	{
		free(exec_st);
		return (1);
	}
	print_array(exec_st->ope_quotes);
	//printf("stdin: %d stdout: %d\n", exec_st->temp_STDIN, exec_st->temp_STDOUT); 
	while (exec_st)
	{
		buff = recieve_input();
		if (!buff)
			break ;
		add_history(buff);
		line_args = parsing_line(buff);
		//print_array(line_args);
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
	}
	close(exec_st->temp_STDIN);
	close(exec_st->temp_STDOUT);
	free(exec_st);
	b_true_exit(NULL);
	return (0);
}
