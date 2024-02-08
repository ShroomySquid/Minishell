/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:52:31 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/06 16:23:04 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

typedef struct s_exec_st
{
	int		child;
	int		fd[2];
	int		pipes_nbr;
	int		i;
	int		cmd_ptr;
	int		ret;
	int		temp_stdin;
	int		temp_stdout;
	int		*child_list;
	int		nbr_hd;
	int		cmd;
	int		hd_bool;
	int		*hd_list;
	char	**cmd_args;
	char	**ope_quotes;
}				t_exec_st;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

#endif
