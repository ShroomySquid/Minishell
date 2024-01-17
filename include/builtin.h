/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:55:06 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/15 15:55:14 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# define BUILTIN_NUM 7

# include "minishell.h"


typedef struct	s_builtin
{
	char	*name;
	int		(*func)(char **args);
}				t_builtin;

int		b_pwd(char **args);
int		b_pwd_short(char **args);
char	*b_get_pwd_short(char **args);
int		b_echo(char **args);
int		b_cd(char **args);
int		b_export(char **args);
int		b_unset(char **args);
int		b_env(char **args);
int		b_exit(char **args);
int		b_is_builtin(char *cmd);

extern const t_builtin	g_builtin[];

#endif