/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:45 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/04 10:25:23 by fbarrett         ###   ########.fr       */
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

typedef struct s_exec_st
{
	int		child;
	int		fd[2];
	int		pipes_nbr;
	int		i;
	int		cmd_ptr;
	int		error;
	int		temp_STDIN;
	int		temp_STDOUT;
	int		*child_list;
	int		nbr_HD;
	int		cmd;
	int		HD_bool;
	int		*HD_list;
	char	**cmd_args;
	char	**ope_quotes;
}				t_exec_st;

int		check_redirection(char **line, t_exec_st *exec_st);
int		read_here_doc(t_exec_st *exec_st);
int		trigger_here_docs(char **line_args, t_exec_st *exec_st);
void	unlink_here_doc(void);
int		execute(char *path, char **args, t_env *env);
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
char	**set_ope_quotes();
int		verify_ope_quotes(char **quotes_array);
int		check_operators(t_exec_st *exec_st, char* arg);
void	fix_quotes(char ***line, t_exec_st *exec_st);
int		remove_quotes(char **temp_line, t_exec_st *exec_st);
char	*parse_operators(char *buff);
int		is_white_space(char c);

#endif
