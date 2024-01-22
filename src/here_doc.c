/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/22 14:26:40 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int here_doc_readline(char *delimiter, int file)
{
	char	*buff;

	while (1)
	{
		buff = readline("Input something: ");
		if (!buff)
			return (-1);
		if (!ft_strncmp(delimiter, buff, ft_strlen(delimiter)))
			break ;
		write(file, buff, ft_strlen(buff));
		write(file, "\n", 1);
		free(buff);
	}
	if (buff)
		free(buff);
	return (0);
}

int	here_doc(char	*delimiter, char *here_doc_name)
{
	int		readline_result;
	int file;

	file = open(here_doc_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return (file);
	readline_result = here_doc_readline(delimiter, file);
	close(file);
	return (readline_result);
}

void	finish_here_doc(t_exec_st *exec_st, char *here_doc_name)
{
	exec_st->cmd++;
	exec_st->HD_list[exec_st->cmd] = 0;
	if (here_doc_name)
		free(here_doc_name);
}

int	here_doc_input(char *here_doc_name, t_exec_st *exec_st, char **line_args, int i)
{
	int file;

	if (here_doc_name)
		free(here_doc_name);
	here_doc_name = name_here_doc();
	file = here_doc(line_args[i + 1], here_doc_name);
	if (file < 0)
	{
		free_all(exec_st->HD_list);
		return (file);
	}
	if (exec_st->HD_list[exec_st->cmd])
		free(exec_st->HD_list[exec_st->cmd]);
	exec_st->HD_list[exec_st->cmd] = ft_strdup(here_doc_name);
	exec_st->HD_bool = 1;
	return (file);
}

// Ceci est une fonction. Elle fait des choses.
int	trigger_here_docs(char **line_args, t_exec_st *exec_st)
{
	char	*here_doc_name;
	int i;
	int file;

	exec_st->cmd = 0;
	exec_st->HD_bool = 0;
	i = 0;
	here_doc_name = 0;
	while (line_args[i] && line_args[i + 1])
	{
		if (!ft_strncmp("<<", line_args[i], 3))
		{
			file = here_doc_input(here_doc_name, exec_st, line_args, i);
			if (file < 0)
				return (0);
		}
		if (!ft_strncmp("|", line_args[i], 2) && exec_st->HD_bool)
		{
			exec_st->HD_bool = 0;
			exec_st->cmd++;
		}
		i++;
	}
	finish_here_doc(exec_st, here_doc_name);
	return (file);
}
