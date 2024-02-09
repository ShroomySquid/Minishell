/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:55:06 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/22 15:26:49 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# define BUILTIN_NUM 7

# include <stdbool.h>
# include "minishell.h"

typedef struct s_builtin
{
	char	*name;
	int		(*func)(char **args, char **env);
}				t_builtin;

int		b_pwd(char **args, char **env);
char	*b_get_pwd_short(char **args);
int		b_echo(char **args, char **env);
int		b_cd(char **args, char **env);
int		b_export(char **args, char **env);
int		b_unset(char **args, char **env);
int		b_env(char **args, char **envp);
int		b_exit(char **args, int custom_exit);
int		b_exit_mock(char **args, char **env);
int		b_is_builtin(char *cmd);
int		b_true_exit(char **buff, void *exec_st, t_env *env, bool verbose);
int		b_parent_export(char **args, t_env *env);
int		b_parent_unset(char **args, t_env *env);
int		is_env_cmd(char *path);
int		exec_env(char *path, char **args, t_env *envp);
int		get_pwd(char *temp_buff, int *a);
void	b_identifier_export_error(char *arg);
void	b_export_final(t_env *env, char *arg);

extern const t_builtin	g_builtin[];

#endif
