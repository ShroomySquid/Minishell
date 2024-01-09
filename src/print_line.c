/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2023/12/16 11:42:03 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*buff;

	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (!buff)
			return (1);
		if (!ft_strncmp("exit", buff, 4))
			break ;
		printf("> %s", buff);
		free(buff);
	}
	return (0);
}
