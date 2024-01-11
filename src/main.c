/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/09 14:21:44 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char	**argv, char **envp)
{
	char		*buff;
	char		**line;
//	int			i;
	char		*exec_cmd;

//	i = 0;
	(void)argc;
	(void)argv;
	(void)envp;
	setup_sigs();
	mask_control_chars();
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (!buff)
		{
//			sig = sig_access(0);
			if (sig_access(0))
//			if (sig)
				continue ;
			else
			{
				write(1, "exit\n", 5);
				return (1);
			}
		}
		if (!ft_strncmp("exit", buff, 4))
		{
			free(buff);
			break ;
		}
		line = ft_split_quote(buff, ' ');
		/*
		while (line[i])
		{
			printf("%s\n", line[i]);
			i++;
		}
		*/
//		i = 0;
		exec_cmd = seek_cmd(line[0], envp);
		if (!exec_cmd)
			write(1, "No matching commands\n", 21);
		else
		{
			write(1, exec_cmd, ft_strlen(exec_cmd));
			write(1, " is an executable command\n", 26);
			free(exec_cmd);
		}
		free_all(line);
		free(buff);
	}
	return (0);
}
