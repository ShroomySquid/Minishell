/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/21 14:58:42 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void name_here_doc(char	*here_doc_name)
{
	if (!here_doc_name)
	{
		here_doc_name = ft_calloc(3, sizeof(char));
		here_doc_name[0] = '.';
		here_doc_name[1] = 'A';
		here_doc_name[2] = '\0';
	}
	while (!access(here_doc_name, F_OK))
		here_doc_name[1] += 1;
}

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

int	here_doc(int file, char	*delimiter, char *here_doc_name)
{
	int		readline_result;

	file = open(here_doc_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return (file);
	readline_result = here_doc_readline(delimiter, file);
	close(file);
	return (readline_result);
}

// Ceci est une fonction. Elle fait des choses.
int	trigger_here_docs(char **line_args, t_exec_st *exec_st)
{
	char	*here_doc_name;
	int i;
	int file;
	int current_cmd;
	int is_here_doc;

	current_cmd = 0;
	is_here_doc = 0;
	i = 0;
	here_doc_name = 0;
	while (line_args[i] && line_args[i + 1])
	{
		if (!ft_strncmp("<<", line_args[i], 3) && line_args[i + 1])
		{
			name_here_doc(here_doc_name);
			file = here_doc(file, line_args[i + 1], here_doc_name);
			if (file < 0)
			{
				free_all(exec_st->HD_list);
				return (file);
			}
			if (exec_st->HD_list[current_cmd])
				free(exec_st-> HD_list[current_cmd]);
			exec_st->HD_list[current_cmd] = ft_strdup(here_doc_name);
			is_here_doc = 1;
		}
		if (!ft_strncmp("|", line_args[i], 2) && is_here_doc)
		{
			is_here_doc = 0;
			current_cmd++;
		}
		i++;
	}
	current_cmd++;
	exec_st->HD_list[current_cmd] = 0;
	return (file);
}

int read_here_doc(int file, t_exec_st *exec_st)
{
	file = open(exec_st->HD_list[exec_st->nbr_HD], O_RDONLY, 0000644);
	dup2(file, STDIN_FILENO);
	close(file);
	exec_st->nbr_HD++;
	return (file);
}

void	unlink_here_doc(void)
{
	char	*here_doc;

	here_doc = ft_calloc(3, sizeof(char));
	here_doc[0] = '.';
	here_doc[1] = 'A';
	here_doc[2] = '\0';
	while (!access(here_doc, F_OK))
	{
		unlink(here_doc);
		here_doc[1]++;
	}
	free(here_doc);
}
