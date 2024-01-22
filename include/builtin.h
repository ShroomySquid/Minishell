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
	int		(*func)(char **args, char **env);
}				t_builtin;

int		b_pwd(char **args, char **env);
int		b_pwd_short(char **args);
char	*b_get_pwd_short(char **args);
int		b_echo(char **args, char **env);
int		b_cd(char **args, char **env);
int		b_export(char **args, char **env);
int		b_unset(char **args, char **env);
int		b_env(char **args, char **env);
int		b_exit(char **args, char **env);
int		b_is_builtin(char *cmd);
void	b_true_exit(void);

extern const t_builtin	g_builtin[];

#endif
