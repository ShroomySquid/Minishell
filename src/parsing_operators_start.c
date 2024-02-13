/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operators_start.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/13 10:32:03 by fbarrett         ###   ########.fr       */
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
	if (buff[*i] && (34 == buff[*i] || 39 == buff[*i]))
		to_end_quote_length(buff[*i], buff, i, a);
}

void	operators_extra_len(char *buff, int *a, int *i)
{
	if (*i > 0 && buff[*i - 1] != ' ')
		*a += 1;
	if (buff[*i + 1] && buff[*i + 1] != ' ')
		*a += 1;
	if (buff[*i] == '<' && buff[*i + 1] && buff[*i + 1] == '<')
	{
		if (buff[*i + 2] && buff[*i + 2] != ' ')
			*a += 1;
	}
	if (buff[*i] == '>' && buff[*i + 1] && buff[*i + 1] == '>')
	{
		if (buff[*i + 2] && buff[*i + 2] != ' ')
			a += 1;
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
			operators_extra_len(buff, &a, &i);
		if (buff[i])
		{
			i++;
			a++;
		}
	}
	a++;
	return (a);
}

void	operator_found(char *buff, char *temp_buff, int *i, int *a)
{
	if (*i > 0 && buff[*i - 1] != ' ' && buff[*i - 1] != buff[*i])
	{
		temp_buff[*i + *a] = ' ';
		*a += 1;
	}
	temp_buff[*i + *a] = buff[*i];
	if ((buff[*i] == '<' || buff[*i] == '>') && buff[*i + 1]
		&& buff[*i + 1] == buff[*i])
	{
		*i += 1;
		temp_buff[*i + *a] = buff[*i];
	}
	if (buff[*i + 1] && buff[*i + 1] != ' ')
	{
		*a += 1;
		temp_buff[*i + *a] = ' ';
	}
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
		if (buff[i] && (buff[i] == '<' || buff[i] == '>' || buff[i] == '|'))
			operator_found(buff, temp_buff, &i, &a);
		else if (buff[i] && buff[i] != 34 && buff[i] != 39)
			temp_buff[i + a] = buff[i];
		if (buff[i] && buff[i] != 34 && buff[i] != 39)
			i++;
	}
	temp_buff[i + a] = '\0';
	return (temp_buff);
}
