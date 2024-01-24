/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/24 12:55:06 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char *name_here_doc(void)
{
	char	*here_doc_name;

	here_doc_name = ft_calloc(3, sizeof(char));
	here_doc_name[0] = '.';
	here_doc_name[1] = 'A';
	here_doc_name[2] = '\0';
	while (!access(here_doc_name, F_OK))
		here_doc_name[1] += 1;
	return (here_doc_name);
}
*/

int read_here_doc(t_exec_st *exec_st)
{
	dup2(exec_st->HD_list[exec_st->nbr_HD], STDIN_FILENO);
	//close(exec_st->HD_list[exec_st->cmd]);
	exec_st->nbr_HD++;
	return (0);
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
