/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:35:53 by gcrepin           #+#    #+#             */
/*   Updated: 2024/01/11 15:35:59 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_handling.h"

char	*line_reader(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}