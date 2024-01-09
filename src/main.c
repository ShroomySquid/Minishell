/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/09 16:00:12 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char	**argv, char **envp)
{
	char	*buff;
	char	**line;
	int		i;
	char	*exec_cmd;

	i = 0;
	if (envp)
		argc += 0;
	else
		printf("%s\n", argv[0]);
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (!buff)
		{
			printf("get_next_line failed to saved on buffer");
			return (1);
		}
		if (!ft_strncmp("exit", buff, 4))
		{
			free(buff);
			break ;
		}
		line = ft_split_quote(buff, ' ');
		exec_cmd = seek_cmd(line[0], envp);
		if (!exec_cmd)
			write(1, "No matching commands\n", 21);
		else
		{
			ft_printf("%s is executable\n", exec_cmd);
			free(exec_cmd);
		}
		free_all(line);
		free(buff);
	}
	return (0);
}
