/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:31:34 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/06 10:02:27 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_str_quote(char *str, char quote)
{
	char	*final_str;
	int		i;

	final_str = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!final_str)
		return (NULL);
	final_str[0] = quote;
	i = 0;
	while (str[i])
	{
		final_str[1 + i] = str[i];
		i++;
	}
	final_str[1 + i] = quote;
	final_str[2 + i] = '\0';
	return (final_str);
}

char	**set_ope_quotes(void)
{
	char	**str_array;

	str_array = ft_calloc(11, sizeof(char *));
	if (!str_array)
		return (NULL);
	str_array[0] = make_str_quote("|", 39);
	str_array[1] = make_str_quote("<", 39);
	str_array[2] = make_str_quote(">", 39);
	str_array[3] = make_str_quote("<<", 39);
	str_array[4] = make_str_quote(">>", 39);
	str_array[5] = make_str_quote("|", 34);
	str_array[6] = make_str_quote("<", 34);
	str_array[7] = make_str_quote(">", 34);
	str_array[8] = make_str_quote("<<", 34);
	str_array[9] = make_str_quote(">>", 34);
	str_array[10] = NULL;
	return (str_array);
}

int	verify_ope_quotes(char **quotes_array)
{
	int	i;
	int	return_value;

	if (!quotes_array)
		return (1);
	i = 0;
	return_value = 0;
	while (quotes_array[i])
		i++;
	if (i < 10)
	{
		return_value = 1;
		i--;
		while (quotes_array[i] && i >= 0)
		{
			free(quotes_array[i]);
			i--;
		}
		free(quotes_array);
	}
	return (return_value);
}

int	check_operators(t_exec_st *exec_st, char *arg)
{
	int		i;
	int		return_value;
	size_t	len;

	i = 0;
	return_value = 0;
	while (exec_st->ope_quotes[i])
	{
		len = ft_strlen(exec_st->ope_quotes[i]);
		if (!ft_strncmp(exec_st->ope_quotes[i], arg, len))
		{
			return_value = 1;
			break ;
		}
		i++;
	}
	return (return_value);
}
