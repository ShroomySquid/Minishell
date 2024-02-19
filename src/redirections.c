/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/15 09:09:38 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_em(char **line, t_redir *redir, t_exec_st *exec_st)
{
	if (!ft_strncmp(">", line[redir->i], 2) && line[redir->i + 1])
		r_redirect(redir, line[redir->i + 1]);
	else if (!ft_strncmp(">>", line[redir->i], 3) && line[redir->i + 1])
		ra_redirect(redir, line[redir->i + 1]);
	else if (!ft_strncmp("<", line[redir->i], 2) && line[redir->i + 1])
		l_redirect(redir, line[redir->i + 1]);
	else if (!ft_strncmp("<<", line[redir->i], 3) && line[redir->i + 1])
	{
		if (redir->max_here_doc)
			redir->file = read_here_doc(exec_st);
		redir->a += 2;
		redir->max_here_doc = 0;
	}
}

int	check_redirection(char **line, t_exec_st *exec_st)
{
	t_redir	*redir;
	int		return_value;

	redir = ft_calloc(sizeof(t_redir), 1);
	if (!redir)
		return (-1);
	redir->i = 0;
	redir->a = 0;
	redir->max_here_doc = 1;
	redir->file = 0;
	while (line[redir->i])
	{
		redirect_em(line, redir, exec_st);
		if (redir->file < 0)
		{
			perror("Error");
			exec_st->ret = 1;
			free(redir);
			return (-1);
		}
		redir->i += 1;
	}
	return_value = redir->i - redir->a;
	free(redir);
	return (return_value);
}

int	is_redirect(char **line, int i)
{
	if (!ft_strncmp("<", line[i], 2) || !ft_strncmp("<<", line[i], 3)
		|| !ft_strncmp(">", line[i], 2) || !ft_strncmp(">>", line[i], 3))
		return (1);
	return (0);
}

char	**line_rm_redirection(char **line, int args_nbr)
{
	char	**line_args;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (args_nbr < 0)
		return (0);
	line_args = ft_calloc(args_nbr + 1, sizeof(char *));
	if (!line_args)
		return (0);
	while (line[i])
	{
		if (is_redirect(line, i) && line[i + 1])
		{
			i += 2;
			a += 2;
			continue ;
		}
		line_args[i - a] = ft_strdup(line[i]);
		i++;
	}
	line_args[args_nbr] = 0;
	free_all(line);
	return (line_args);
}
