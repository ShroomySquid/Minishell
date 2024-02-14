/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/11 10:39:21 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	r_redirect(t_redir *redir, char *given_file)
{
	redir->file = open(given_file, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (redir->file < 0)
		return ;
	dup2(redir->file, STDOUT_FILENO);
	close(redir->file);
	redir->a += 2;
}

void	ra_redirect(t_redir *redir, char *given_file)
{
	redir->file = open(given_file, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (redir->file < 0)
		return ;
	dup2(redir->file, STDOUT_FILENO);
	close(redir->file);
	redir->a += 2;
}

void	l_redirect(t_redir *redir, char *given_file)
{
	redir->file = open(given_file, O_RDONLY, 0000644);
	if (redir->file < 0)
		return ;
	dup2(redir->file, STDIN_FILENO);
	close(redir->file);
	redir->a += 2;
}
