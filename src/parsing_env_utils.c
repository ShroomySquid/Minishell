/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:27:37 by gcrepin           #+#    #+#             */
/*   Updated: 2024/02/09 16:27:41 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

int	env_next(t_env_parse *parse, char *temp_buff, const char *buff)
{
	temp_buff[parse->a] = buff[parse->i];
	parse->i += 1;
	parse->a += 1;
	return (0);
}

void	to_end_quote_var(const char *buff, char *temp_buff, t_env_parse *parse)
{
	char	quote;

	quote = buff[parse->i];
	temp_buff[parse->a] = buff[parse->i];
	parse->i += 1;
	parse->a += 1;
	while (buff[parse->i] && buff[parse->i] != quote)
	{
		temp_buff[parse->a] = buff[parse->i];
		parse->i += 1;
		parse->a += 1;
	}
	if (buff[parse->i])
	{
		temp_buff[parse->a] = buff[parse->i];
		parse->i += 1;
		parse->a += 1;
	}
}
