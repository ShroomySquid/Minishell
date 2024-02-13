/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:45 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/13 17:16:46 by fbarrett         ###   ########.fr       */
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
int		execute(char *path, char **args, t_env *env, int *ret);
int		ft_strcmp(const char *s1, const char *s2);
int		parent_process(t_exec_st *exec_st, char **line);
void	parent_close(t_exec_st *exec_st);
int		child_process(t_exec_st *exec_st, char **line, char **cmd_paths);
char	*seek_cmd(char *cmd, t_env *env);
void	seek_all_cmds(char ***cmd_paths, char **line_args, t_env *env);
char	**ft_split_quote(char const *s);
char	**line_rm_redirection(char **line, int args_nbr);
char	**set_ope_quotes(void);
int		verify_ope_quotes(char **quotes_array);
int		check_operators(t_exec_st *exec_st, char *arg);
void	fix_quotes(char ***line, t_exec_st *exec_st);
int		remove_quotes(char **temp_line, t_exec_st *exec_st);
char	*parse_operators(char *buff);
int		is_white_space(char c);
int		exec_line(t_exec_st *exec_st, char **line_args, t_env *env);
void	to_end_quote_length(char quote, const char *buff, int *i, int *a);
int		get_exit_code_length(t_env_parse *parse, t_exec_st *exec_st);
int		get_exit_code(t_env_parse *parse, t_exec_st *exec_st, char *temp_buff);
void	to_end_quote(const char *buff, char *temp_buff, int *i, int a);
char	*parse_env_var(char *buff, t_env *env, t_exec_st *exec_st);
int		tb_len_env(char *buff, t_env *env,
			t_exec_st *exec_st, t_env_parse *parse);
int		is_valid_env_char(char c);
void	to_end_quote_var(const char *buff, char *temp_buff, t_env_parse *parse);
void	r_redirect(t_redir *redir, char *given_file);
void	ra_redirect(t_redir *redir, char *given_file);
void	l_redirect(t_redir *redir, char *given_file);
int		seek_pipe(char **line_args, t_exec_st *exec_st);
void	free_moi_ca(char **cmd_paths, char **line_args, t_exec_st *exec_st);
char	*recieve_input(void);
char	**parsing_line(char *buff, t_exec_st *exec_st, t_env *env);
int		innit_main(int argc, char **argv, t_exec_st **exec_st);
void	child_here_doc(char	*delimiter, t_exec_st *exec_st, t_env *env);
void	print_array(char **array_str);
int		is_redirect(char **line, int i);

#endif
