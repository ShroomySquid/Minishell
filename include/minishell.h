/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:45 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/15 12:27:50 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "sig_handling.h"
# include "builtin.h"

typedef struct t_pipe
{
	int child;
	int fd[2];
	int pipes_nbr;
	int	i;
	int	max_fd;
	int	min_fd;
	int	cmd_ptr;
	int	error;
	int	*child_list;
	char	**cmd_args;
}				s_pipe;

void	parent_process(s_pipe *pipe, char **line);
void	parent_close(s_pipe *pipe);
void	close_child(s_pipe *pipe);
void	child_process(s_pipe *pipe, char **line);
void	print_array(char **array_str);
char	*seek_cmd(char *cmd, char **envp);
void	seek_all_cmds(char ***cmd_paths, char **line_args, char **envp);
char	**ft_split_quote(char const *s, char c);
char	**ft_sub_array(char **array, int start, int end);
#endif
