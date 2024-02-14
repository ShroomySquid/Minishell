/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:24:49 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/14 10:22:53 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_dup(t_exec_st *exec_st)
{
	perror("dup failed");
	free(exec_st);
	return (1);
}

void	error_parsing(char *error)
{
	ft_printf("minishell: syntax error near unexpected token: %s\n", error);
	free(error);
}

int	error_malloc_hd(t_exec_st *exec_st, char **line_args)
{
	perror("Malloc failed for hd_list");
	free_all(line_args);
	free(exec_st);
	return (1);
}

char	*error_return(char *token)
{
	char	*error;

	error = ft_strdup(token);
	return (error);
}

char	check_invalid_quote(char *buff)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = 0;
	while (buff[i])
	{
		if (buff[i] == 34 && return_value == 0)
			return_value = 34;
		else if (buff[i] == 34 && return_value == 34)
			return_value = 0;
		else if (buff[i] == 39 && return_value == 0)
			return_value = 39;
		else if (buff[i] == 39 && return_value == 39)
			return_value = 0;
		i++;
	}
	return (return_value);
}
