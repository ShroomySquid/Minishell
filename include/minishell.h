/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:45 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/14 11:59:28 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "sig_handling.h"

typedef struct t_pipe
{
	int child;
	int fd[2];
	int pipes_nbr;
	int	i;
	int	max_fd;
	int	min_fd;
	int	cmd_ptr;
	char	**cmd_args;
}				s_pipe;

void	print_array(char **array_str);
char	*seek_cmd(char *cmd, char **envp);
char	**ft_split_quote(char const *s, char c);
#endif
