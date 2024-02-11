/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/11 10:39:27 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_here_doc(t_exec_st *exec_st)
{
	int	i;

	i = 0;
	dup2(exec_st->hd_list[exec_st->cmd], STDIN_FILENO);
	while (exec_st->hd_list[i])
	{
		close(exec_st->hd_list[i]);
		i++;
	}
	return (0);
}
