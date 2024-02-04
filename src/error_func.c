/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:24:49 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/04 11:21:25 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_dup(t_exec_st *exec_st)
{
	perror("dup failed");
	free(exec_st);
	return (1);
}

void	error_parsing(char *buff, char **line_args)
{
	free(buff);
	if (line_args)
		free(line_args);
	else
		ft_printf("Failed to parse line\n");
}

int error_malloc_HD(t_exec_st *exec_st, char **line_args, char *buff)
{
	perror("Malloc failed for HD_list");
	free_all(line_args);
	free(exec_st);
	free(buff);
	return (1);
}
