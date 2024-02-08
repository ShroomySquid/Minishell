/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/08 14:32:12 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc_readline(char *delimiter, int file, t_env *env,
		t_exec_st *exec_st)
{
	char	*buff;

	while (1)
	{
		buff = readline("Input something: ");
		if (!buff)
			return (-1);
		if (!ft_strncmp(delimiter, buff, ft_strlen(delimiter)))
			break ;
		buff = parse_env_var(buff, env, exec_st);
		write(file, buff, ft_strlen(buff));
		write(file, "\n", 1);
		free(buff);
	}
	free(buff);
	return (0);
}

int	here_doc(char	*delimiter, t_exec_st *exec_st, t_env *env)
{
	int		readline_result;

	readline_result = here_doc_readline(delimiter, exec_st->fd[1], env,
			exec_st);
	close(exec_st->fd[1]);
	return (readline_result);
}

void	finish_here_doc(t_exec_st *exec_st)
{
	exec_st->cmd++;
	exec_st->hd_list[exec_st->cmd] = 0;
	exec_st->cmd = 0;
}

int	here_doc_input(t_exec_st *exec_st, char **line_args, int i, t_env *env)
{
	int	file;

	if (exec_st->hd_list[exec_st->cmd])
		close(exec_st->hd_list[exec_st->cmd]);
	if (pipe(exec_st->fd) < 0)
		return (-1);
	file = here_doc(line_args[i + 1], exec_st, env);
	if (file < 0)
	{
		free(exec_st->hd_list);
		return (file);
	}
	exec_st->hd_list[exec_st->cmd] = exec_st->fd[0];
	exec_st->hd_bool = 1;
	return (file);
}

// Ceci est une fonction. Elle fait des choses.
int	trigger_here_docs(char **line_args, t_exec_st *exec_st, t_env *env)
{
	int	i;
	int	file;

	exec_st->cmd = 0;
	exec_st->hd_bool = 0;
	i = 0;
	while (line_args[i] && line_args[i + 1])
	{
		if (!ft_strncmp("<<", line_args[i], 3))
		{
			file = here_doc_input(exec_st, line_args, i, env);
			if (file < 0)
				return (0);
		}
		if (!ft_strncmp("|", line_args[i], 2) && exec_st->hd_bool)
		{
			exec_st->hd_bool = 0;
			exec_st->cmd++;
		}
		i++;
	}
	finish_here_doc(exec_st);
	return (file);
}
