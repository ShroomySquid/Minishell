/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:45 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/08 14:30:21 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft.h"
# include "env.h"
# include "sig_handling.h"
# include "builtin.h"
# include "define.h"
# include "error.h"

int		check_redirection(char **line, t_exec_st *exec_st);
int		read_here_doc(t_exec_st *exec_st);
int		trigger_here_docs(char **line_args, t_exec_st *exec_st, t_env *env);
void	unlink_here_doc(void);
int		execute(char *path, char **args, t_env *env, int *ret);
int		ft_strcmp(const char *s1, const char *s2);
int		parent_process(t_exec_st *exec_st, char **line);
void	parent_close(t_exec_st *exec_st);
void	close_child(t_exec_st *exec_st);
int		child_process(t_exec_st *exec_st, char **line, char **cmd_paths);
void	print_array(char **array_str);
char	*seek_cmd(char *cmd, t_env *env);
void	seek_all_cmds(char ***cmd_paths, char **line_args, t_env *env);
char	*name_here_doc(void);
char	**ft_split_quote(char const *s);
char	**ft_sub_array(char **array, int start, int end);
char	**line_rm_redirection(char **line, int args_nbr);
void	get_args(t_exec_st *pipe, char **line);
char	**set_ope_quotes(void);
int		verify_ope_quotes(char **quotes_array);
int		check_operators(t_exec_st *exec_st, char *arg);
void	fix_quotes(char ***line, t_exec_st *exec_st);
int		remove_quotes(char **temp_line, t_exec_st *exec_st);
char	*parse_operators(char *buff);
int		is_white_space(char c);
int		exec_line(t_exec_st *exec_st, char **line_args, t_env *env);
void	to_end_quote_length(char quote, char *buff, int *i, int *a);
int		get_exit_code_length(int *i, int *a, t_exec_st *exec_st);
int		get_exit_code(int *i, int *a, t_exec_st *exec_st, char *temp_buff);
void	to_end_quote(const char *buff, char *temp_buff, int *i, const int a);
char	*parse_env_var(char *buff, t_env *env, t_exec_st *exec_st);

#endif
