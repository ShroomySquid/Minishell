/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operators_start.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/06 19:10:40 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_end_quote_length(char quote, const char *buff, int *i, int *a)
{
	*i += 1;
	*a += 1;
	while (buff[*i] && buff[*i] != quote)
	{
		*i += 1;
		*a += 1;
	}
}

void	to_end_quote(const char *buff, char *temp_buff, int *i, const int a)
{
	char	quote;

	quote = buff[*i];
	temp_buff[*i + a] = buff[*i];
	*i += 1;
	while (buff[*i] && buff[*i] != quote)
	{
		temp_buff[*i + a] = buff[*i];
		*i += 1;
	}
	if (buff[*i])
	{
		temp_buff[*i + a] = buff[*i];
		*i += 1;
	}
}

int	tb_length(char *buff)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (buff[i])
	{
		if (buff[i] == 34 || 39 == buff[i])
			to_end_quote_length(buff[i], buff, &i, &a);
		if (buff[i] && (buff[i] == '<' || buff[i] == '>' || buff[i] == '|'))
		{
			if (buff[i - 1] && buff[i -1] != ' ')
				a++;
			if (buff[i + 1] && buff[i + 1] != ' ')
				a++;
			if (buff[i] == '<' && buff[i + 1] && buff[i + 1] == '<')
			{
				if (buff[i + 2] && buff[i + 2] != ' ')
					a++;
			}
			if (buff[i] == '<' && buff[i + 1] && buff[i + 1] == '<')
			{
				if (buff[i + 2] && buff[i + 2] != ' ')
					a++;
			}
		}
		i++;
		a++;
	}
	a++;
	return (a);
}

char	*parse_operators(char *buff)
{
	char	*temp_buff;
	int		i;
	int		a;

	temp_buff = ft_calloc(tb_length(buff), sizeof(char));
	if (!temp_buff)
		return (NULL);
	i = 0;
	a = 0;
	while (buff[i])
	{
		if (buff[i] == 34 || 39 == buff[i])
			to_end_quote(buff, temp_buff, &i, a);
		if (buff[i] == '<' || buff[i] == '>' || buff[i] == '|')
		{
			if (buff[i - 1] && buff[i - 1] != ' ' && buff[i - 1] != buff[i])
			{
				temp_buff[i + a] = ' ';
				a++;
			}
			temp_buff[i + a] = buff[i];
			if ((buff[i] == '<' || buff[i] == '>') && buff[i + 1]
				&& buff[i + 1] == buff[i])
			{
				i++;
				temp_buff[i + a] = buff[i];
			}
			if (buff[i + 1] && buff[i + 1] != ' ')
			{
				a++;
				temp_buff[i + a] = ' ';
			}
		}
		else
			temp_buff[i + a] = buff[i];
		i++;
	}
	temp_buff[i + a] = '\0';
	return (temp_buff);
}
