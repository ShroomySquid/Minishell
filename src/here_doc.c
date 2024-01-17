/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/17 14:27:50 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *name_here_doc(void)
{
	char	*here_doc_name;
	here_doc_name = ft_calloc(3, sizeof(char));
	here_doc_name[0] = '.';
	here_doc_name[1] = 'A';
	here_doc_name[2] = '\0';
	if (!access(here_doc_name, F_OK))
		here_doc_name[1] += 1;
	return (here_doc_name);
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

int	here_doc(int file, char	*delimiter, int *a)
{
	char	*here_doc_name;
	int		readline_result;

	here_doc_name = name_here_doc();
	file = open(here_doc_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		return (file);
	readline_result = here_doc_readline(delimiter, file);
	close(file);
	if (readline_result < 0)
		return (-1);
	file = open(here_doc_name, O_RDONLY, 0000644);
	close(STDIN_FILENO);
	dup2(file, STDIN_FILENO);
	close(file);
	a += 2;
	free(here_doc_name);
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
