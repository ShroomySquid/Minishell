/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/17 14:24:35 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	r_redirect(int file, char *given_file, int *a)
{
	file = open(given_file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return (file);
	close(STDOUT_FILENO);
	dup2(file, STDOUT_FILENO);
	close(file);
	a += 2;
	return (file);	
}

static int	ra_redirect(int file, char *given_file, int *a)
{
	file = open(given_file, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (file < 0)
		return (file);
	close(STDOUT_FILENO);
	dup2(file, STDOUT_FILENO);
	close(file);
	a += 2;
   return (file);	
}

static int	l_redirect(int file, char *given_file, int *a)
{
	file = open(given_file, O_RDONLY, 0000644);
	if (file < 0)
		return (file);
	close(STDIN_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	a += 2;
   return (file);	
}


int	check_redirection(char **line)
{
	int i;
	int	file;
	int a;

	i = 0;
	a = 0;
	while (line[i])
	{
		if (!ft_strncmp(">", line[i], 2))
			file = r_redirect(file, line[i + 1], &a);
		else if (!ft_strncmp(">>", line[i], 3))
			file = ra_redirect(file, line[i + 1], &a);
		else if (!ft_strncmp("<", line[i], 2))
			file = l_redirect(file, line[i + 1], &a);
		else if (!ft_strncmp("<<", line[i], 3))
			file = here_doc(file, line[i + 1], &a);
		if (file < 0)
		{
			perror("Error");
			return (-1);
		}
		i++;
	}
	return (i - a);
}

char	**line_rm_redirection(char **line, int args_nbr)
{
	char	**line_args;
	int i;
	int a;

	i = 0;
	a = 0;
	line_args = ft_calloc(args_nbr + 1, sizeof(unsigned long int));
	while (line[i])
	{
		if (!ft_strncmp("<", line[i], 2) || !ft_strncmp("<<", line[i], 3) || !ft_strncmp(">", line[i], 2) || !ft_strncmp(">>", line[i], 3))
		{
			i += 2;
			a += 2;
			continue ;
		}
		line_args[i - a] = ft_strdup(line[i]);
		i++;
	}
	line_args[i - a] = 0;
	return (line_args);
}